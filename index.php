<?php
require_once('address.inc');
/*
$recordset = new Recordset('Address');
$recordset->addRecord(new Address('18 Devon rd', '', 'Edison', 'NJ', '08820', 'USA'));
$recordset->addRecord(new Address('343 Willowbrook dr', '', 'North Brunswick', 'NJ', '08902', 'USA'));
*/
$recordset = Recordset::load('Address');
echo $recordset->getTsv();
//$recordset->save();