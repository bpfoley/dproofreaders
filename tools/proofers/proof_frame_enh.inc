<?php
include_once($relPath.'http_headers.inc');
include_once($relPath.'site_vars.php');
include_once($relPath.'slim_header.inc');
include_once('PPage.inc');
include_once('image_block_enh.inc');
include_once('button_menu.inc');


function echo_proof_frame_enh( $ppage )
{
    global $userP;

    slim_header( _("Proofreading Page"),TRUE,FALSE);

    ibe_echo_script();
    ?>
        <script language="JavaScript" type="text/javascript">
            <!--
            function ldAll()
            {top.initializeStuff(1);}
            // -->
        </script>
        <style type="text/css">
            <!--
            body {
                font-family: verdana, arial, helvetica, sans-serif;
                font-size: 12px;
                color:#000000;
                background-color:#CDCDC1;
                text-align:center;
                overflow:hidden;
            }
            <?php ibe_echo_styles(); ?>
            #tbtext {
                border:1px solid #000000;
                text-align:center;
                overflow:auto;
            }
            #tdtop {
                border:1px solid #000000;
                background-color:#CDC0B0;
                padding:2px;
            }
            #tdtext {
                border:1px solid #000000;
                background-color:#CDCDC1;
                padding:2px;
            }
            #tdbottom {
                border:1px solid #000000;
                background-color:#EEDFCC;
                padding:2px;
            }
            #text_data {
                padding:2px;
                background-color:#FFF8DC;
                color:#000000;
            }
            .dropsmall {
                font-size: 75%;
                background-color:#FFF8DC;
            }
            .boxnormal {
                background-color:#FFF8DC;
            }
            -->
        </style>
        </head>
        <body
            text="#000000"
            topmargin="0"
            onload="ldAll()">
            <?php

                if ($userP['i_layout']==1)
                    {$iWidth=$userP['v_zoom'];}
                else {$iWidth=$userP['h_zoom'];}
                $iWidth=round((1000*$iWidth)/100);

                ibe_echo_block( $ppage->url_for_image(), $iWidth );

            ?>
            <div id="controlframe" align="center">
                <form
                    name="editform" id="editform"
                    method="POST"
                    action="processtext.php">
                    <?php $ppage->echo_hidden_fields(); ?>
                    <table
                        id="tbtext"
                        cellspacing="0"
                        align="center">
                        <tr>
                            <td id="tdtop" valign="middle">
                                <?php echo_button_menu( $ppage ); ?>
                            </td>
                        </tr>
                        <tr>
                            <td id="tdtext" valign="top">
                                <?php $ppage->echo_proofing_textarea(); ?>
                            </td>
                        </tr>
                        <tr>
                            <td id="tdbottom" valign="top">
                                <?php $ppage->echo_info(); ?>
                            </td>
                        </tr>
                    </table>
                </form>
            </div>
        </body>
    </html>
    <?php
}

// vim: sw=4 ts=4 expandtab
?>