<!DOCTYPE html>

<html>
    
    <head>
        
        <!-- 
             idea stolen from: http://stackoverflow.com/questions/901115/how-can-i-get-query-string-values-in-javascript
             user: Andy E
        -->
        <?= "<script>var urlParams = ".json_encode($_GET, JSON_HEX_TAG).";</script>"; ?>

        <!-- http://getbootstrap.com/ -->
        <link href="/css/bootstrap.min.css" rel="stylesheet"/>

        <!-- app's own CSS -->
        <link href="/css/styles.css" rel="stylesheet"/>

<?php if (isset($ENABLE_GOOGLE_MAPS)): ?>
        <!-- https://developers.google.com/maps/documentation/javascript/ -->
        <script src="https://maps.googleapis.com/maps/api/js"></script>

        <!-- http://google-maps-utility-library-v3.googlecode.com/svn/tags/markerwithlabel/1.1.10/ -->
        <script src="/js/markerwithlabel_packed.js"></script>

        <!-- http://jquery.com/ -->
        <script src="/js/jquery-1.11.3.min.js"></script>

        <!-- http://getbootstrap.com/ -->
        <script src="/js/bootstrap.min.js"></script>

        <!-- http://underscorejs.org/ -->
        <script src="/js/underscore-min.js"></script>

        <!-- https://github.com/twitter/typeahead.js/ -->
        <script src="/js/typeahead.jquery.min.js"></script>

        <!-- app's own JavaScript -->
        <script src="/js/scripts.js"></script>
<?php endif; ?>

        <title>Mashup</title>

    </head>
    
    <body>