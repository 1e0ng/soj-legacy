<?php

class Pager
{
    private $curPos;
    private $totalSize;
    private $pageSize;
    private $bPrevNextOnly;

    private $pagerString = '';
    public function __construct($curPos, $totalSize, $pageSize = 20, $bPrevNextOnly = false)
    {
        $this->curPos = $curPos;
        $this->totalSize = $totalSize;
        $this->pageSize = $pageSize;

        doPage();
    }
    private function doPage()
    {

    }
}

?>
