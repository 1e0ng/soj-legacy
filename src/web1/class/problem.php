<?php
class Problem
{
    private $pid;
    private $problemName;
    private $accepted;
    private $submitted;
    /*
    private $discription;
    private $input;
    private $output;
    private $inputCase;
    private $outputCase;
     */
    private $timeLimit;
    private $memoryLimit;

    public function __construct($pid, $problemName, $accepted, $submitted, $timeLimit, $memoryLimit)
    {
        $this->pid = $pid;
        $this->problemName = $problemName;
        $this->accepted = $accepted;
        $this->submitted = $submitted;
        $this->memoryLimit = $memoryLimit;
        $this->timeLimit = $timeLimit;
    }

    public function getPid()
    {
        return $this->pid;
    }
    public function getProblemName()
    {
        return $this->problemName;
    }
    public function getAcceptedSubmit()
    {
        return $this->accepted;
    }
    public function getTotalSubmit()
    {
        return $this->totalSubmit;
    }
}

class ProblemManager
{
    public static function findProblemBy($type, $arg, $top, $size)
    {
        global $g_db;

        $sql = "select pid, problemName, accepted, submitted, timeLimit, memoryLimit from problem where ";
        if($type == "id")
        {
            $arg = $arg;
            $sql .= "pid = $arg";
        }
        else if($type == "name")
        {
            $arg = $g_db->escapeString($arg);
            $sql .= "problemName like '%$arg%'";
        }
        else
        {
            assert(false);
        }
        $sql .= " limit $top, $size";

        $out = array();
        $res = $g_db->query($sql);
        while($p = $res->fetch_assoc())
        {
            $out[] = new Problem($p["pid"], $p["problemName"], $p["accepted"], $p["submitted"], $p["timeLimit"], $p["memoryLimit"]);
        } 
        return $out;
    }
    public static function countProblem($name)
    {
        global $g_db;

        $name = $g_db->escapeString($name);
        $sql = "select count(*) from problem where problemName like '%$name%'";
        $res = $g_db->query($sql);
        return $res->num_rows;
    }
}
?>
