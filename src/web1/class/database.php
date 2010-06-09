<?php

class Database
{
    /*
     * singleton related part
     */

    private static $instance = null;

    private function __clone(){}

    public static function getInstance()
    {
        if(self::$instance == null)
        {
            $c = __CLASS__;
            self::$instance = new $c;
        }
        return $c;
    }

    /*
     * interface
     */
    private $conn = null;
    private $queryTimes = 0;

    private function __construct()
    {
        require_once('../config.php');
        $this->conn = new mysqli();
        @$this->conn->connect(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_DATABASE);
        if($myerror = mysqli_connect_error())
        {
            require_once('../function/util.php');
            OjDie('Database error!');
        }
    }

    //guarrantee it returns true or a result object`
    public function query($sql)
    {
        $queryTimes++;

        if(!($ret = $this->conn->query($sql)))
        {
            require_once('../function/util.php');
            OjDie('Database error!');
        }
        return $ret;
    }

    public function escapeString($str)
    {
        return $this->conn->real_escape_string($str);
    }

    public function __get($name)
    {
        switch($name)
        {
        case "errno":
            return $this->conn->errno;break;
        case "error":
            return $this->conn->error;break;
        case "queryTimes":
            return $this->queryTimes;break;
        }
        assert(false);
    }
}

?>
