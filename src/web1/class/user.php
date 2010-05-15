<?php
class User
{
    /*
	//comments are the corresponding database column name
	private $userid = 0;//uid
	private $username = '';//username
	private $nickname = '';//nickname
	private $gender = '';//gender
	private $password = '';//password
	private $email = '';//email
	private $lastIp = '0.0.0.0';//pending
	private $lastLoginTime = '';//pending
	private $school = '';//school
	private $registerTime = '';//registerTime

	private $acceptedSubmit = 0;//accepted
    private $totalSubmit = 0;//submitted
     */

    private $properties = array();

    public function __construct()
    {
        $this->properties['userid'] = 0;
        $this->properties['username'] = '';
        $this->properties['nickname'] = '';
        $this->properties['gender'] = '';
        $this->properties['password'] = '';
        $this->properties['email'] = '';
        $this->properties['lastIp'] = '0.0.0.0';
        $this->properties['lastLoginTime'] = '';
        $this->properties['school'] = '';
        $this->properties['registerTime'] = '';
        $this->properties['acceptedSubmit'] = 0;
        $this->properties['totalSubmit'] = 0;
    }

    public function initFromDb($conn, $userid)
    {
        $sql = "select uid, username, nickname, gender, email, school, registerTime, accepted, submitted " . 
            "from user where uid = $userid";
        if($result = $conn->query($sql))
        {
            $obj = $result->fetch_object();
            $this->properties['userid'] = $obj->uid;
            $this->properties['username'] = $obj->username;
            $this->properties['nickname'] = $obj->nickname;
            $this->properties['gender'] = $obj->gender;
            $this->properties['lastIp'] = $obj->email;
            $this->properties['school'] = $obj->school;
            $this->properties['registerTime'] = $obj->registerTime;
            $this->properties['acceptedSubmit'] = $obj->accepted;
            $this->properties['totalSubmit'] = $obj->submitted;
        }
    }
    public function initFromCookie()
    {
    }
    
    public function __set($name, $value)
    {
        if(array_key_exists($name, $this->properties))
        {
            $this->properties[$name] = $value;
        }
        else
            throw new Exception('Bad property name!');
    }
    public function __get($name)
    {
        if(array_key_exists($name, $this->properties))
        {
            return $this->properties[$name];
        }
        else
            throw new Exception('Bad property name!');
        return NULL;
    }
}
?>
