<?php
class Address extends Record {
	public $address1;
	public $address2;
	public $city;
	public $state;
	public $country;
	public $zipcode;
	//USAGE: $recordset->addRecord(new Address('343 Willowbrook dr', '', 'North Brunswick', 'NJ', '08902', 'USA'));
	public function __construct($address1, $address2, $city, $state, $country, $zipcode) {
		$this->address1 = $address1;
		$this->address2 = $address2;
		$this->city = $city;
		$this->state = $state;
		$this->country = $country;
		$this->zipcode = $zipcode;
	}
}

class Record {
    public function getTsv() {
		$output = array();
		foreach($this as $key=>$value) {
			array_push($output, $value);
		}
		return(implode("\t", $output));
    }
    public function getHeader() {
		$output = array();
		foreach($this as $key=>$value) {
			array_push($output, $key);
		}
		return(implode("\t", $output));
    }
}

class RecordSet {
	public $name;
	public $records;
	//USAGE: $recordset = new Recordset('Address');
	public function __construct($name) {
		if(!isset($name)) trigger_error("RecordSet must have a name");
		else {
			$this->name = $name;
			$this->records = array();
		}
	}
	public function addRecord($record) {
		array_push($this->records, $record);
	}
	public function getTsv() {
		$output = array();
		if(count($this->records) > 0) {
			array_push($output, $this->records[0]->getHeader());
			foreach($this->records as $record) {
				array_push($output, $record->getTsv());
			}
		}
		return(implode("\n", $output));
	}
	public function save() {
		file_put_contents($this->name.'.zip', gzencode(serialize($this)));
	}
	//Returns a Recordset object
	//USAGE (from outside class): $recordset = Recordset::load('Address');
	static public function load($name) {
		return(unserialize(gzdecode(file_get_contents("$name.zip"))));
	}
}