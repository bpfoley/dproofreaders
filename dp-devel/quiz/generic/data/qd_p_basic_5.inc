<?php
include_once('quiz_defaults.inc');

function quizsolved()
{
  global $pguser;
  if (isset($pguser))
      record_quiz_attempt($pguser,"p_basic_5","pass");
}

$browser_title                = _("Basic Proofreading Quiz");
$welcome                      = "<h2>" . _("Basic Proofreading Quiz, part 5") . "</h2>\n" .
                                    "<p>" . _("Try to correct the text on the bottom left, so it matches the text in the image above following the Proofreading Guidelines. When done click 'check'.") . "</p>";
$ocr_text                     = "We ask ourselves how Byron's poem\nYou have the Pyrrhic dance as yet,\nWhere is the Pyrrhic phalanx\ngone?\nOf two such lessons, why forget\nThe nobler and the manlier one?\nis related to these well known words:\n\nWhen in the course of human events, it\nbecomes necessary for one people to\ndissolve . . . political hands.\n\nNot at all. we suspect.";
$solutions                    = array("We ask ourselves how Byron's poem\n\nYou have the Pyrrhic dance as yet,\nWhere is the Pyrrhic phalanx\ngone?\nOf two such lessons, why forget\nThe nobler and the manlier one?\n\nis related to these well known words:\n\nWhen in the Course of human events, it\nbecomes necessary for one people to\ndissolve ... political bands.\n\nNot at all, we suspect.");
$solved_message               = "<h2>" . _("Quiz successfully solved") . "</h2>\n" .
                                    "<p>" . _("Congratulations, no errors found!") . "</p>\n" .
                                    "<h3>" . _("Handy Fact") . "</h3>\n" .
                                    "<p>" . sprintf(_("DPCustomMono2 is a custom font that helps proofreaders notice scannos. You can <a href='%1\$s' target='_blank'>compare it with other fonts</a> or read how to <a href='%2\$s' target='_blank'>download and install it</a>."), "../../faq/font_sample.php", $custom_font_url) . "</p>";


// error messages

$messages["hands"] = array(
    "message_text" => "<h2>" . _("Scanno") . "</h2>\n" .
        "<p>" . _("There is still a 'scanno': an '<tt>h</tt>' in the text where there is a '<tt>b</tt>' in the image.") . "</p>",
    "hints" => array(),
);
$messages["capital"] = array(
    "message_text" => "<h2>" . _("Scanno") . "</h2>\n" .
        "<p>" . _("There is still a 'scanno': a lower case '<tt>c</tt>' in the text where there is a capital '<tt>C</tt>' in the image.") . "</p>",
    "hints" => array(),
);
$messages["indent"] = array(
    "message_text" => "<h2>" . _("Indentation") . "</h2>\n" .
        "<p>" . _("Leave the indentation of text for the formatting rounds.  During proofreading, leave the text left aligned.") . "</p>",
    "hints" => array(),
    "guideline" => "formatting",
);


// error checks

$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("hands"), "case_sensitive" => TRUE, "error" => "hands");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("course"), "case_sensitive" => TRUE, "error" => "capital");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("all."), "case_sensitive" => TRUE, "error" => "P_commascanno");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array(". . ."), "case_sensitive" => TRUE, "error" => "P_ellspaced");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("e ... p"), "case_sensitive" => TRUE, "error" => "P_midellips");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("\""), "case_sensitive" => TRUE, "error" => "P_addedquotes");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("phalanx gone"), "case_sensitive" => TRUE, "error" => "P_joinline");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("poem\nYou", "?\nis"), "case_sensitive" => TRUE, "error" => "P_poetryblanklines");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("\n "), "case_sensitive" => TRUE, "error" => "P_indent");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("/*", "*/"), "case_sensitive" => TRUE, "error" => "P_poemmarkup");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("/#", "#/"), "case_sensitive" => TRUE, "error" => "P_blockmarkup");

// vim: sw=4 ts=4 expandtab