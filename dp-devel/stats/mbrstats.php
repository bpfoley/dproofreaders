<?
$relPath='./../pinc/';
include($relPath.'v_site.inc');
include($relPath.'connect.inc');
$db_Connection=new dbConnect();

$today = getdate();
$midnight = mktime(0,0,0,$today['mon'],$today['mday'],$today['year']);
$prev_midnight = $midnight - 86400;

//Find out if the script has been run once already for today
$result = mysql_query("SELECT MAX(date_updated) FROM member_stats");
	if (mysql_result($result,0,0) == $midnight && empty($_GET['testing'])) {
		echo "<center>This script has already been run today!</center>";
	} else {
	//Update the page count rank for the previous day
	$result = mysql_query("SELECT u_id, pagescompleted FROM users ORDER BY pagescompleted DESC");
		$rankArray = "";
		$i = 1;

		while ($row = mysql_fetch_assoc($result)) {
			$user_id = $row['u_id'];
			if ($row['pagescompleted'] == 0) { $rankArray['rank'][$user_id] = 0; continue; }
			if ($row['pagescompleted'] == $lastcompleted) {
				$rankArray['rank'][$user_id] = $lastrank;
				$lastrank = $lastrank;
    			} else {
    				$rankArray['rank'][$user_id] = $i;
    				$lastrank = $i;
   			}
    			$lastcompleted = $row['pagescompleted'];
    			if ($i == 1) { $lastrank = 1; }
    			$i++;
		}

	//Update member_stats with previous days page count
	$result = mysql_query("SELECT u_id, total_pagescompleted FROM member_stats WHERE date_updated = $prev_midnight");
		while ($row = mysql_fetch_assoc($result)) {
			$prevDayCount[$row['u_id']]['total_pagescompleted'] = $row['total_pagescompleted'];
		}

	$result = mysql_query("SELECT u_id, pagescompleted FROM users");
		while($row = mysql_fetch_assoc($result)) {
			$todaysCount = $row['pagescompleted'] - $prevDayCount[$row['u_id']]['total_pagescompleted'];
			$updateCount = mysql_query("INSERT INTO member_stats (u_id, date_updated, daily_pagescompleted, total_pagescompleted, rank) VALUES (".$row['u_id'].", $midnight, $todaysCount, ".$row['pagescompleted'].", ".$rankArray['rank'][$row['u_id']].")");
		}
	}
?>