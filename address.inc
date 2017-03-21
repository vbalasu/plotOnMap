<?php
class Address extends Record {
	public $address1;
	public $address2;
	public $city;
	public $state;
	public $country;
	public $zipcode;
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
		file_put_contents($this->name.'.serialize', gzcompress(serialize($this)));
	}
	//Returns a Recordset object
	static public function load($name) {
		return(unserialize(gzuncompress(file_get_contents("$name.serialize"))));
	}
}