<?php
abstract class User
{
	private $userid = 0;//uid
    private $usertype = 0;//type
	private $username = '';//username
	private $nickname = 'guest';//nickname
	private $gender = 0;//gender
	private $password = '';//password
	private $email = '';//email
    private $lastLanguage = 0;//last used language
	private $lastLoginIp = '0.0.0.0';//pending
	private $lastLoginTime = '';//pending
	private $school = '';//school
	private $registerTime = '';//registerTime

	private $acceptedSubmit = 0;//accepted
    private $totalSubmit = 0;//submitted

    //construct from a record
    public function __construct($ar)
    {
    }

    public function getUserId()
    {
        return $this->userid;
    }
    public function setUserId($uid)
    {
        $this->userid = (int)$uid;
    }
    public function getUserType()
    {
        return $this->usertype;
    }
    public function getUserTypeString()
    {
        if($this->usertype == 0)
            return "guest";
        else if($this->usertype == 1)
            return "acmer";
        else if($this->usertype == 2)
            return "admin";
        else
            return "";
    }
    public function setUsertype($type)
    {
        if($type == "acmer" || $type == 1)
            $this->usertype = 1;
        else if($type == "admin" || $type == 2)
            $this->usertype = 2;
        else
            $this->usertype = 0;
    }
    public function getUsername()
    {
        return $this->username;
    }
    public function setUsername($name)
    {
        $this->username = $name;
    }
    public function getNickname()
    {
        return $this->nickname;
    }
    public function setNickname($name)
    {
        $this->nickname = $name;
    }
    public function getGender()
    {
        return $this->gender;
    }
    public function getStringGender()
    {
        switch($this->gender)
        {
        case 1:
            return "male";break;
        case 2:
            return "female";break;
        case 0:
        default:
            return "unknown";break;
        }
    }
    public function setGender($gender)
    {
        if($gender == "male" || $gender == 1)
            $this->gender = 1;
        else if($gender == "female" || gender == 2)
            $this->gender = 2;
        else
            $this->gender = 0;
    }
    public function getPassword()
    {
        return $this->password;
    }
    public function setPassword($pswd)
    {
        $this->password = encryptPassword($pswd);
    }
    public function getEmail()
    {
        return $this->email;
    }
    public function setEmail($email)
    {
        $this->email = $email;
    }
    public function getLastLanguage()
    {
        return $this->lastLanguage;
    }
    public function setLastLanguage($lan)
    {
        $this->lastLanguage = (int)$lan;
    }
    public function getLastLoginIp()
    {
        return $this->lastLoginIp;
    }
    public function setLastLoginIp($ip)
    {
        $this->lastLoginIp = $ip;
    }
    public function getLastLoginTime()
    {
        return $this->lastLoginTime;
    }
    public function setLastLoginTime($time)
    {
        $this->lastLoginTime = $time;
    }
    public function getSchool()
    {
        return $this->school;
    }
    public function setSchool($school)
    {
        $this->school = $school;
    }
    public function getRegisterTime()
    {
        return $this->registerTime;
    }
    public function setRegisterTime($time)
    {
        return $this->registerTime = $time;
    }
    public function getTotalSubmit()
    {
        return $this->totalSubmit;
    }
    public function setTotalSubmit($total)
    {
        $this->totalSubmit = (int)$total;
    }
    public function getAcceptedSubmit()
    {
        return $this->acceptedSubmit;
    }
    public function setAcceptedSubmit($accepted)
    {
        $this->accepted = (int)$accepted;
    }

    public abstract function getType();
    
    //used from register, must be examined first
    public function initFromForm($form)
    {
    }

    //used for user logining in or listing users
    public function initFromDBSimple($assoc)
    {
        $this->userid = (int)$assoc["uid"];
        $this->usertype = (int)$assoc["type"];
        $this->nickname = $assoc["nickname"];
        $this->totalSubmit = (int)$assoc["totalSubmit"];
        $this->acceptedSubmit = (int)$assoc["acceptedSubmit"];
    }

    //used for viewing user info
    public function initFromDBDetailed($assoc)
    {
        initFromDBSimple($assoc);
        $this->email = $assoc["email"];
        $this->gender = (int)$assoc["gender"];
        $this->school = $assoc["school"];
        $this->lastLanguage = $assoc["lastLanguage"];
        $this->registerTime = $assoc["registerTime"];
        $this->lastLoginIp = $assoc["lastLoginIp"];
        $this->lastLoginTime = $assoc["lastLoginTime"];
    }

    //subclass should override this function if they add new field
    public function toArraySimple()
    {
        $a = array(
            "UserId" => $this->userid,
            "Nickname" => $this->nickname,
            "AcceptedSubmit" => $this->acceptedSubmit,
            "TotalSubmit" => $this->totalSubmit
        );
        return $a;
    }
    //some properties are not included because they are not public profile
    public function toArrayDetailed()
    {
        $a = array(
            "UserId" => $this->userid,
            "Nickname" => $this->nickname,
            "Gender" => $this->gender,
            "Email" => $this->email,
            "LastLoginIp" => $this->LastLoginIp,
            "LastLoginTime" => $this->LastLoginTime,
            "School" => $this->school,
            "RegisterTime" => $this->registerTime,
            "AcceptedSubmit" => $this->acceptedSubmit,
            "TotalSubmit" => $this->totalSubmit
        );
        return $a;
    }

    //check to see if their formats are correct and contain any valid chars
    public static function checkUsername($username)
    {
        global $g_error;

        if($username == "")
        {
            $g_error["username"] = "Username can't be empty!";
            return false;
        }
        if(strlen($username) < 4 || strlen($username) > 16)
        {
            $g_error["username"] = "Username length must be between 4 and 16!";
            return false;
        }
        if(!preg_match("/^[a-zA-Z][a-zA-Z0-9_]*$/", $username))
        {
            $g_error["username"] = "Your username must match this pattern ^[a-zA-Z][a-zA-Z0-9_]*$";
            return false;
        }
        return true;
    }
    public static function checkPassword($password1, $password2)
    {
        global $g_error;

        if($password1 == "" || $password2 == "")
        {
            $g_error["password"] = "Password can't be empty!";
            return false;
        }
        if($password1 != $password2)
        {
            $g_error["password"] = "Passwords are not match!";
            return false;
        }
        if(strlen($password1) > 16)
        {
            $g_error["password"] = "Password length must be less than 17";
            return false;
        }
        return false;
    }
    public static function checkNickname($nickname)
    {
        global $g_error;

        if($nickname == "")
        {
            $g_error["nickname"] = "Nickname can't be empty!";
            return false;
        }
        if(strlen($nickname) > 64)
        {
            $g_error["nickname"] = "Nickname length must be less than 65!";
            return false;
        }
        if(preg_match("/<|>|\"|'/", $nickname))
        {
            $g_error["nickname"] = "Nick name can't contain invalid characters such as <>/[]!";
            return false;
        }
        return true;
    }
    public static function checkEmail($email)
    {
        global $g_error;

        if($email == "")
            return true;
        if(strlen($email) > 128)
        {
            $g_error["email"] = "Email address is too long!";
            return false;
        }
        if(!preg_match("/^[a-zA-Z0-9._%-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/", $email))
        {
            $g_error["email"] = "Email address format invalid!";
        }
        return true;
    }
    public static function checkSchool($school)
    {
        global $g_error;
        
        if($school == "")
            return true;
        if(strlen($school) > 32)
        {
            $g_error["school"] = "School name is too long!";
            return false;
        }
        if(preg_match("/<|>|\"|'/", $school))
        {
            $g_error["school"] = "School name can't contain invalid characters such as <>/[]!";
            return false;
        }
        return true;
    }
    public static function encryptPassword($pswd)
    {
        return md5($pswd);
    }
}

/*
class Guest extends User
{
    public function __construct($ar)
    {
        parent::__construct($ar);
    }
    public function getType()
    {
        return "guest";
    }
}

class Acmer extends User
{
    public function __construct($ar)
    {
        parent::__construct($ar);
    }
    public function getType()
    {
        return "acmer";
    }
}

class Admin extends User
{
    public function __construct($ar)
    {
        parent::__construct($ar);
    }
    public function getType()
    {
        return "admin";
    }
}

class UserFactory
{
    private static $instance = null;
    private function __construct(){}
    private function __clone(){}
    public function getInstance()
    {
        if(self::$instance == null)
        {
            $c = __CLASS__;
            self::$instance = new $c;
        }
        return self::$instance;
    }
    public function getUser($type)
    {
        switch($type)
        {
        case "2":
        case "acmer":
            return new Acmer();
        case "3":
        case "admin":
            return new Admin();
        case "1":
        case "guest":
        default:
            return new Guest();
            break;:
        }
        return null;
    }
}
 */

class UserManager
{
    //load a user from id or username
    public static function loadUser($arg, $bId = false)
    {
        global $g_db, $g_error;

        $arg = $g_db->escapeString($arg);

        if($bId)
        {
            $sql = "select uid, nickname, type, accepted, submitted, gender, email, gender, school, lastLanguage, lastLoginIp, lastLoginTime
                from user where uid = $arg";
        }
        else
        {
            $sql = "select uid, nickname, type, accepted, submitted, gender, email, gender, school, lastLanguage, lastLoginIp, lastLoginTime
                from user where username = $arg";
        }
        $res = $g_db->query($sql);
        if($res->num_rows == 0)
        {
            return false;
        }
        else
        {
            $ar = $res->fetch_assoc();
            $user = new User();
            $user->initFromDBDetailed($ar);
            return $user;
        }
    }

    //load top $top users
    public static function loadTopUser($top, $size)
    {
        global $g_db, $g_error;

        $sql = "select uid, nickname, accepted, submitted from user
            order by accepted desc, submitted asc limit $top, $size";
        $res = $g_db->query($sql);
        $users = array();
        while($assoc = $res->fetch_assoc())
        {
            $user = new User();
            $user->initFromDBSimple($assoc);
            $users[] = $user;
        }
        return $users;
    }

    //login user
    public static function login($username, $password)
    {
        global $g_db, $g_error;

        if($user = loadUser($username))
        {
            if($user->getPassword() != User::encryptPassword($password))
            {
                $g_error["login"] = "Username or password is wrong!";
                return false;
            }
            $_SESSION["user"] = $user;
            return true;
        }
        else
        {
            $g_error["login"] = "Username or password is wrong!";
            return false;
        }
    }

    //register a new user
    public static function register($user)
    {
        global $g_db, $g_error;

        if(!User::checkUsername($user["username"]))
        {
            $g_error["register"] = $g_error["username"];
            return false;
        }
        $user["username"] = $g_db->escapeString($user["username"]);

        if(!User::checkPassword($user["password1"], $user["password2"]))
        {
            $g_error["register"] = $g_error["password"];
            return false;
        }
        $user["password"] = User::encryptPassword($user["password1"]);

        if(!User::checkNickname($user["nickname"]))
        {
            $g_error["register"] = $g_error["nickname"];
            return false;
        }
        $user["nickname"] = $g_db->escapeString($user["nickname"]);

        if(!User::checkEmail($user["email"]))
        {
            $g_error["register"] = $g_error["email"];
            return false;
        }
        $user["email"] = $g_db->escapeString($user["email"]);

        if(!User::checkSchool($user["school"]))
        {
            $g_error["register"] = $g_error["school"];
            return false;
        }
        $user["school"] = $g_db->escapeString($user["school"]);

        if(isUsernameExisted($user["username"]))
        {
            $g_error["username"] = "Username existed!";
            $g_error["register"] = $g_error["username"];
            return false;
        }
        if(isNicknameExisted($user(["nickname"])))
        {
            $g_error["nickname"] = "Nickname existed!";
            $g_error["register"] = $g_error["nickname"];
            return false;
        }

        date_default_timezone_set("Asia/Shanghai");
		$tm = date('Y-m-d H:i:s');
        $ip = $_SERVER['REMOTE_ADDR'];

        $sql = "insert into user (username, nickname, password, email, school, gender, registerTime, lastLoginIp, lastLoginTime, lastLanguage)
				values('$username', '$nickname', '$pswd', '$email', '$school', $gender, '$tm', '$ip', '$tm', 0)";
        $g_db->query($sql);

        return true;
    }

    //create a user instance representing current user through cookies or sessions
    public static function getCurrentUser()
    {
        if(isset($_SESSION["user"]))
            return $_SESSION["user"];
        else
        {
            $user = new User();
            $_SESSION["user"] = $user;
            return $user;
        }
    }

    //check to see if this name existed
    public static function isUsernameExisted($name)
    {
        global $g_db;

        $sql = "select uid from user where username = " . $g_db->escapeString($name);
        $res = $g_db->query($sql);
        return $res->num_rows > 0;
    }

    public static function isNicknameExisted($name)
    {
        global $g_db;

        $sql = "select uid from user where nickname = " . $g_db->escapeString($name);
        $res = $g_db->query($sql);
        return $res->num_rows > 0;
    }
}    
?>

