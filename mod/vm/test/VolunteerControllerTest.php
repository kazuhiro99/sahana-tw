<?php
/**
 * VolunteerControllerTest
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Antonio Alcorn
 * @author       Giovanni Capalbo
 * @author		Sylvia Hristakeva
 * @author		Kumud Nepal
 * @author		Ernel Wint
 * @copyright    Lanka Software Foundation - http://www.opensource.lk
 * @copyright    Trinity Humanitarian-FOSS Project - http://www.cs.trincoll.edu/hfoss
 * @package      sahana
 * @subpackage   vm
 * @tutorial
 * @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
 * Public License (LGPL)
 */
// Call VolunteerControllerTest::main() if this source file is executed directly.
if (!defined("PHPUnit_MAIN_METHOD")) {
    define("PHPUnit_MAIN_METHOD", "VolunteerControllerTest::main");
}
/**
 * Test class for VolunteerController.
 * Generated by PHPUnit_Util_Skeleton on 2007-06-19 at 11:08:45.
 */
class VolunteerControllerTest extends PHPUnit_Framework_TestCase {
    /**
     * Sets up the fixture, for example, open a network connection.
     * This method is called before a test is executed.
     *
     * @access protected
     */
    protected function setUp() {
        $this->fixture = new VolunteerController();
        global $global, $dao;
        $global = array('approot' => realpath(dirname(__FILE__)) . '/../../../');
        require_once ($global['approot'] . '3rd/adodb/adodb.inc.php');
        //Make the connection to $global['db']
        $global['db'] = NewADOConnection('mysql');
        $global['db']->Connect(TEST_DB_HOST, TEST_DB_USER, TEST_DB_PASSWD, TEST_DB_NAME);
        error_reporting(E_ALL ^ E_NOTICE);
        $dao = new DAO($global['db']);
    }
    /**
     * Tears down the fixture, for example, close a network connection.
     * This method is called after a test is executed.
     *
     * @access protected
     */
    protected function tearDown() {
    }
    /**
     * @todo Implement testControlHandler().
     */
    public function testControlHandler() {
        // Remove the following line when you implement this test.
        $this->markTestIncomplete("This test has not been implemented yet.");
    }
    /**
     * Tests testValidateAddForm().
     */
    public function testValidateAddForm() {
        //valid
        $test1 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "SKILL_MGR_APPLY" => "on");
        $test2 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "dob" => "1986-07-25", "hrs_avail_start" => "1:20", "hrs_avail_end" => "10:50", "reg_account" => "true", "user_name" => "name", "pass1" => "pass", "pass2" => "pass", "SKILL_MGR_APPLY" => "on");
        $test3 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "dob" => "", "SKILL_MGR_APPLY" => "on", "SKILL_ANI4" => "off", "SKILL_ANI8" => "on");
        $test4 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "reg_account" => "not_true", "user_name" => "name", "pass1" => "pass", "pass2" => "pass", "SKILL_MGR_APPLY" => "on");
        //empty array
        $test_1 = array();
        //invalid full_name
        $test_2 = array("start_date" => "2000-12-20", "end_date" => "2001-02-15", "SKILL_MGR_APPLY" => "on");
        $test_3 = array("full_name" => "", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "SKILL_MGR_APPLY" => "on");
        //invalid start_date
        $test_4 = array("full_name" => "ed", "end_date" => "2001-02-15", "SKILL_MGR_APPLY" => "on");
        $test_5 = array("full_name" => "ed", "start_date" => "1982-02-29", "end_date" => "2001-02-15", "SKILL_MGR_APPLY" => "on");
        $test_6 = array("full_name" => "ed", "start_date" => "1982-56-29", "end_date" => "2001-02-15", "SKILL_MGR_APPLY" => "on");
        //invalid end_date
        $test_7 = array("full_name" => "ed", "start_date" => "2000-12-20", "SKILL_MGR_APPLY" => "on");
        $test_8 = array("full_name" => "ed", "start_date" => "1982-01-29", "end_date" => "gh-gh-gh", "SKILL_MGR_APPLY" => "on");
        $test_9 = array("full_name" => "ed", "start_date" => "1982-06-29", "end_date" => "", "SKILL_MGR_APPLY" => "on");
        //end_date before start date
        $test_10 = array("full_name" => "ed", "start_date" => "2003-12-20", "end_date" => "2001-02-15", "SKILL_MGR_APPLY" => "on");
        //invalid dob if present
        $test_11 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "dob" => "2010-07-25", "SKILL_MGR_APPLY" => "on");
        $test_12 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "dob" => "fksdfj", "SKILL_MGR_APPLY" => "on");
        $test_13 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "dob" => "19986-15-25", "SKILL_MGR_APPLY" => "on");
        //invalid start hour if present
        $test_14 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "hrs_avail_start" => "35:78", "SKILL_MGR_APPLY" => "on");
        $test_15 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "hrs_avail_start" => "444:20:00", "SKILL_MGR_APPLY" => "on");
        //invalid end hour if present
        $test_16 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "hrs_avail_end" => "4:60", "SKILL_MGR_APPLY" => "on");
        $test_17 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "hrs_avail_end" => "4:674:99", "SKILL_MGR_APPLY" => "on");
        //invalid skills
        $test_18 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15");
        $test_19 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "SKILL_MGR_APPLY" => "", "SKILL_ANI4" => "off", "SKILL_ANI8" => "fdg");
        //invalid user name or password if specified
        $test_20 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "reg_account" => "true", "user_name" => "", "pass1" => "pass", "pass2" => "pass", "SKILL_MGR_APPLY" => "on");
        $test_21 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "reg_account" => "true", "user_name" => "    ", "pass1" => "pass", "pass2" => "pass", "SKILL_MGR_APPLY" => "on");
        $test_22 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "reg_account" => "true", "user_name" => "ed", "pass1" => "pass", "pass2" => "pass", "SKILL_MGR_APPLY" => "on");
        $test_23 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "reg_account" => "true", "user_name" => "name", "pass1" => "", "pass2" => "pass", "SKILL_MGR_APPLY" => "on");
        $test_24 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "reg_account" => "true", "user_name" => "name", "pass1" => "pass", "pass2" => "   ", "SKILL_MGR_APPLY" => "on");
        $test_25 = array("full_name" => "ed", "start_date" => "2000-12-20", "end_date" => "2001-02-15", "reg_account" => "true", "user_name" => "name", "pass1" => "pass", "pass2" => "Pass", "SKILL_MGR_APPLY" => "on");
        $this->assertTrue($this->fixture->validateAddForm($test1));
        $this->assertTrue($this->fixture->validateAddForm($test2));
        $this->assertTrue($this->fixture->validateAddForm($test3));
        $this->assertTrue($this->fixture->validateAddForm($test4));
        $this->assertFalse($this->fixture->validateAddForm($test_1));
        $this->assertFalse($this->fixture->validateAddForm($test_2));
        $this->assertFalse($this->fixture->validateAddForm($test_3));
        $this->assertFalse($this->fixture->validateAddForm($test_4));
        $this->assertFalse($this->fixture->validateAddForm($test_5));
        $this->assertFalse($this->fixture->validateAddForm($test_6));
        $this->assertFalse($this->fixture->validateAddForm($test_7));
        $this->assertFalse($this->fixture->validateAddForm($test_8));
        $this->assertFalse($this->fixture->validateAddForm($test_9));
        $this->assertFalse($this->fixture->validateAddForm($test_10));
        $this->assertFalse($this->fixture->validateAddForm($test_11));
        $this->assertFalse($this->fixture->validateAddForm($test_12));
        $this->assertFalse($this->fixture->validateAddForm($test_13));
        $this->assertFalse($this->fixture->validateAddForm($test_14));
        $this->assertFalse($this->fixture->validateAddForm($test_15));
        $this->assertFalse($this->fixture->validateAddForm($test_16));
        $this->assertFalse($this->fixture->validateAddForm($test_17));
        $this->assertFalse($this->fixture->validateAddForm($test_18));
        $this->assertFalse($this->fixture->validateAddForm($test_19));
        $this->assertFalse($this->fixture->validateAddForm($test_20));
        $this->assertFalse($this->fixture->validateAddForm($test_21));
        $this->assertFalse($this->fixture->validateAddForm($test_22));
        $this->assertFalse($this->fixture->validateAddForm($test_23));
        $this->assertFalse($this->fixture->validateAddForm($test_24));
        $this->assertFalse($this->fixture->validateAddForm($test_25));
    }
    /**
     * Implement testValidateChangePassForm().
     */
    public function testValidateChangePassForm() {
        $test = array("cur_pass" => "pass", "pass1" => "blah", "pass2" => "blah");
        $test1 = array("cur_pass" => "", "pass1" => "blah", "pass2" => "blah");
        $test2 = array("cur_pass" => "    ", "pass1" => "blah", "pass2" => "blah");
        $test3 = array("cur_pass" => "pass", "pass1" => "", "pass2" => "blah");
        $test4 = array("cur_pass" => "pass", "pass1" => "blah", "pass2" => "    ");
        $test5 = array("cur_pass" => "pass", "pass1" => "blah", "pass2" => "Blah");
        $this->assertTrue($this->fixture->validateChangePassForm($test));
        $this->assertFalse($this->fixture->validateChangePassForm($test1));
        $this->assertFalse($this->fixture->validateChangePassForm($test2));
        $this->assertFalse($this->fixture->validateChangePassForm($test3));
        $this->assertFalse($this->fixture->validateChangePassForm($test4));
        $this->assertFalse($this->fixture->validateChangePassForm($test5));
    }
    /**
     * @todo Implement testValidateSendMessageForm().
     */
    public function testValidateSearchForm() {
        $test1 = array("vol_name" => "ed");
        $test2 = array("vol_iden" => "dsjs");
        $test3 = array("start_date" => "2000-12-30", "end_date" => "2001-07-19");
        $test4 = array("SKILL_MGR_APPLY" => "on");
        $test5 = array("unassigned" => "true");
        $test20 = array("start_date" => "2000-12-30");
        //invalid start and end dates
        $test7 = array("end_date" => "2001-07-19");
        $test8 = array("start_date" => "200-12-30", "end_date" => "2001-07-19");
        $test9 = array("start_date" => "2000-12-30", "end_date" => "2001-0-19");
        $test10 = array("start_date" => "2000-60-30", "end_date" => "2001-07-19");
        $test11 = array("start_date" => "2004-12-30", "end_date" => "2001-07-19");
        $test12 = array("start_date" => "2000-12-30", "end_date" => "2000-12-19");
        $test21 = array("start_date" => "2000-12-30", "date_constraint" => "full_date");
        $test22 = array("end_date" => "2000-12-30", "date_constraint" => "full_date");
        //all empty
        $test13 = array("");
        //skills are not valid if specified
        $test14 = array("SKILL_MGR_APPLY" => "not_on");
        //the id is less than 4 chars
        $test15 = array("vol_id" => "123");
        $this->assertTrue($this->fixture->validateSearchForm($test1));
        $this->assertTrue($this->fixture->validateSearchForm($test2));
        $this->assertTrue($this->fixture->validateSearchForm($test3));
        $this->assertTrue($this->fixture->validateSearchForm($test4));
        $this->assertTrue($this->fixture->validateSearchForm($test5));
        $this->assertTrue($this->fixture->validateSearchForm($test20));
        $this->assertFalse($this->fixture->validateSearchForm($test7));
        $this->assertFalse($this->fixture->validateSearchForm($test8));
        $this->assertFalse($this->fixture->validateSearchForm($test9));
        $this->assertFalse($this->fixture->validateSearchForm($test10));
        $this->assertFalse($this->fixture->validateSearchForm($test11));
        $this->assertFalse($this->fixture->validateSearchForm($test12));
        $this->assertFalse($this->fixture->validateSearchForm($test13));
        $this->assertFalse($this->fixture->validateSearchForm($test14));
        $this->assertFalse($this->fixture->validateSearchForm($test15));
        $this->assertFalse($this->fixture->validateSearchForm($test21));
        $this->assertFalse($this->fixture->validateSearchForm($test22));
        //check if location is valid if specified
        $_POST["levels"] = 3;
        $_POST["1"] = "country";
        $this->assertTrue($this->fixture->validateSearchForm(array()));
        unset($_POST['levels']);
        unset($_POST['1']);
    }
    public function testValidateSendMessageForm() {
        $this->assertTrue($this->fixture->validateSendMessageForm(array("to" => array("me", "you"), "message" => "message")));
        $this->assertFalse($this->fixture->validateSendMessageForm(array("to" => array(), "message" => "message")));
        $this->assertFalse($this->fixture->validateSendMessageForm(array("to" => array("me"), "message" => "")));
        $this->assertFalse($this->fixture->validateSendMessageForm(array()));
    }
}
?>