
<html lang="es-MX">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href="./CSS/materialize.min.css">
    <script src="./JS/materialize.min.js"></script>
    <script src="./JS/jquery.js"></script>
    <title>Arduino</title>
</head>

<body>

    <div class="navbar-fixed">
        <nav>
            <div class="nav-wrapper">
                <a href="./" class="brand-logo center">Arduino</a>
            </div>
        </nav>
    </div>

    <div class="row">
        <div class="col s2 m3">

        </div>
        <div class="col s8 m6">
            <div class="card white">
                <div class="card-content black-text">
                    <span class="card-title black-text">Leds</span>
                    Led 1:
                    <div class="switch">
                        <label>
                            Off
                            <input id="led1" name="led1" type="checkbox"
                                <?php
                                    if($_SERVER["REQUEST_METHOD"] == "GET") {

                                        if(isset($_GET["led1"])) {
                                            if($_GET["led1"] == "ON") {
                                                echo "checked";
                                            }
                                        }
                                    }
                                ?>
                            >
                            <span class="lever"></span>
                            On
                        </label>
                    </div>
                    <br>

                    Led 2:
                    <div class="switch">
                        <label>
                            Off
                            <input id="led2" name="led2" type="checkbox"
                                <?php
                                    if($_SERVER["REQUEST_METHOD"] == "GET") {

                                        if(isset($_GET["led2"])) {
                                            if($_GET["led2"] == "ON") {
                                                echo "checked";
                                            }
                                        }
                                    }
                                ?>
                            >
                            <span class="lever"></span>
                            On
                        </label>
                    </div>

                </div>
            </div>
        </div>
    </div>

    <div class="row">
        <div class="col s2 m3">

        </div>

        <div class="col s8 m6">
            <div class="card white">
                <div class="card-content black-text">
                <span class="card-title black-text">Entradas analogicas</span>
                    
                <table class="responsive-table centered highlight">
                    <thead>
                    <tr>
                        <th>Pin</th>
                        <th>Estado</th>
                    </tr>
                    </thead>

                    <tbody id="tablaAnalogica">
                        
                    </tbody>
                </table>

                </div>
            </div>
        </div>

    </div>

    <div class="row">
        <div class="col s2 m3">

        </div>

        <div class="col s8 m6">
            <div class="card white">
                <div class="card-content black-text">
                
                <span class="card-title black-text">Entradas digitales</span>

                <table class="responsive-table centered highlight">
                    <thead>
                    <tr>
                        <th>Pin</th>
                        <th>Estado</th>
                    </tr>
                    </thead>

                    <tbody id="tablaDigital">
                        
                    </tbody>
                </table>

                </div>
            </div>
        </div>

    </div>

    <a href="./" class="centered">Refrescar</a>

    <script src="./JS/index.js" type="module"></script>

</body>

</html>