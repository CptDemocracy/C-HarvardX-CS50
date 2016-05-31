<?php

    /**
     * Looks up news articles for specified geography. Retuns an array of
     * associative arrays, each of which has two keys: link and title.
     */
    function lookup($geo)
    {
        // if this geo was cached
        if (isset($_SESSION["cache"], $_SESSION["cache"][$geo]))
        {
            // within the past hour
            if (time() < $_SESSION["cache"][$geo]["timestamp"] + 60 * 60)
            {
                // return cached articles
                return $_SESSION["cache"][$geo]["articles"];
            }
        }

        // (soon-to-be numerically indexed) array of articles
        $articles = [];
        
        // headers for proxy servers
        $headers = [
            "Accept" => "*/*",
            "Connection" => "Keep-Alive",
            "User-Agent" => sprintf("curl/%s", curl_version()["version"])
        ];
        $context = stream_context_create([
            "http" => [
                "header" => implode(array_map(function($value, $key) { return sprintf("%s: %s\r\n", $key, $value); }, $headers, array_keys($headers))),
                "method" => "GET"
            ]
        ]);

        // download RSS from Google News if possible
        $contents = @file_get_contents("http://news.google.com/news?geo=" . urlencode($geo) . "&output=rss", false, $context);
        if ($contents !== false)
        {
            // parse RSS
            $rss = @simplexml_load_string($contents);
            if ($rss !== false)
            {
                // iterate over items in channel
                foreach ($rss->channel->item as $item)
                {
                    // add article to array
                    $articles[] = [
                        "link" => (string) $item->link,
                        "title" => (string) $item->title
                    ];
                }

                // cache articles
                if (!isset($_SESSION["cache"]))
                {
                    $_SESSION["cache"] = [];
                }
                $_SESSION["cache"][$_GET["geo"]] = [
                    "articles" => $articles,
                    "timestamp" => time()
                ];
            }
        }

        // else from the Onion
        else
        {
            $contents = @file_get_contents("http://www.theonion.com/feeds/rss", false, $context);
            if ($contents !== false)
            {
                // parse RSS
                $rss = @simplexml_load_string($contents);
                if ($rss !== false)
                {
                    // iterate over items in channel
                    foreach ($rss->channel->item as $item)
                    {
                        // add article to array
                        $articles[] = [
                            "link" => (string) $item->link,
                            "title" => (string) $item->title
                        ];
                    }
                }
            }
        }

        return $articles;
    }

    /**
     * Borrowed from the PSET7 staff-provided code base.
     * 
     * (Hey, they do it all the time with the Call of Duty games -
     * "reusing assets" I think they call it <3)
     * 
     * Apologizes to user with message.
     */
    function apologize($message)
    {
        render("apology.php", ["message" => $message]);
    }
    
    /**
     * Borrowed from the PSET7 staff-provided code base.
     * 
     * Renders view, passing in values.
     */
    function render($view, $values = [])
    {
        // if view exists, render it
        if (file_exists("../views/{$view}"))
        {
            // extract variables into local scope
            extract($values);

            require("../views/header.php");
            require("../views/nav.php");
            require("../views/{$view}");
            require("../views/footer.php");
            exit;
        }

        // else err
        else
        {
            trigger_error("Invalid view: {$view}", E_USER_ERROR);
        }
    }
    
    /**
     * Borrowed from the PSET7 staff-provided code base.
     * 
     * Redirects user to location, which can be a URL or
     * a relative path on the local host.
     *
     * http://stackoverflow.com/a/25643550/5156190
     *
     * Because this function outputs an HTTP header, it
     * must be called before caller outputs any HTML.
     */
    function redirect($location)
    {
        if (headers_sent($file, $line))
        {
            trigger_error("HTTP headers already sent at {$file}:{$line}", E_USER_ERROR);
        }
        header("Location: {$location}");
        exit;
    }
    
    /**
     * Borrowed from the PSET7 staff-provided code base.
     * 
     * Logs out current user, if any.  Based on Example #1 at
     * http://us.php.net/manual/en/function.session-destroy.php.
     */
    function logout()
    {
        // unset any session variables
        $_SESSION = [];

        // expire cookie
        if (!empty($_COOKIE[session_name()]))
        {
            setcookie(session_name(), "", time() - 42000);
        }
    }
    
    function sendMail($destAddr, $subject, $msg)
    {
        require_once("libphp-phpmailer/class.phpmailer.php");
        
        // instantiate mailer
        $mail = new PHPMailer();
        
        $mail->IsSMTP();
        $mail->Host = "smtp.gmail.com";
        $mail->Port = 587;
        $mail->SMTPAuth = true;
        $mail->SMTPSecure = "tls";
        $mail->Username = "happycs50mapsbot@gmail.com";
        $mail->Password = "";
        
        // set From:
        $mail->SetFrom("happycs50mapsbot@gmail.com");
        
        // set To:
        $mail->AddAddress($destAddr);
        
        // set Subject:
        $mail->Subject = $subject;
        
        // set body
        $mail->Body = $msg;
        
        // no need to clear addresses here since we just return
        
        // send mail
        return $mail->Send();
    }
    
    /**
     * Generates a random string using shuffling. I googled "random string generation 
     * in PHP" when I remembered the shuffle algorithm and decided I should implement
     * the function myself. However, I decided not to use the shuffle algorithm for
     * this one to be able to generate strings of any length. (The shuffle algorithm
     * would limit us to the length of $chars).
     */
    function generateRandomString($len)
    {
        $chars = array_merge(range('A', 'Z'), range('a', 'z'), range('0', '9'));
        $charsLen = count($chars);
        
        $randStr = "";
        for ($i = 0; $i < $len; ++$i) 
        {
            $randIndex = mt_rand(0, $charsLen - 1); // inclusive upper bound
            $randStr .= $chars[$randIndex];
        }
        
        return $randStr;
    }
    
    function success($message)
    {
        render("success.php", ["message" => $message]);
    }
?>