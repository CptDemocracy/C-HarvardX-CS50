<?php
    require_once("libphp-phpmailer/class.phpmailer.php");

    function sendMail($destAddr, $subject, $msg)
    {
        // instantiate mailer
        $mail = new PHPMailer();
        
        $mail->IsSMTP();
        $mail->Host = "smtp.gmail.com";
        $mail->Port = 587;
        $mail->SMTPAuth = true;
        $mail->SMTPSecure = "tls";
        $mail->Username = "happycs50financebot@gmail.com";
        $mail->Password = "";
        
        // set From:
        $mail->SetFrom("happycs50financebot@gmail.com");
        
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
?>