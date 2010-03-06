<?php
class Role
{
    private $id;
    private $name;

    public function __construct($id, $name)
    {
        $this->id = $id;
        $this->name = $name;
    }
    
    public function __set($name, $value)
    {
        if(strcmp($name, 'id') == 0)
            $id = $value;
        else if(strcmp($name, 'name') == 0)
            $name = $value;
        throw new Exception("Bad role member!");
    }

    public function __get($name)
    {
        if(strcmp($name, 'id') == 0)
            return $this->id;
        else if(strcmp($name, 'name') == 0)
            return $this->name;
        throw new Exception("Bad role member!");
    }
}
class RoleManager
{
    const INVALID = 0;
    const VISITOR = 1;
    const ACMER = 2;
    const ADMIN = 3;

    private $roles = array();

    private static $instance = NULL;

    private function __construct()
    {
        $this->roles[] = new Role(RoleManager::INVALID, 'invalid role');
        $this->roles[] = new Role(RoleManager::VISITOR, 'visitor');
        $this->roles[] = new Role(RoleManager::ACMER, 'acmer');
        $this->roles[] = new Role(RoleManager::ADMIN, 'admin');
    }
    private function __clone(){}
    
    static public function getInstance()
    {
        if(self::$instance == NULL)
            self::$instance = new RoleManager();
        return self::$instance;
    }

	public function getRole($user)
	{
        return $this->roles[$user];
	}
}

echo RoleManager::getInstance()->getRole(2)->name;

?>
