<?php
/**Registration related forms for Inventories of the Inventory Management System
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage ims
*/
global $global;
include_once $global['approot'] . "/inc/lib_form.inc";
include_once $global['approot'] . "/inc/lib_errors.inc";
require_once $global['approot'] . "/inc/lib_location.inc";
include_once $global['approot'] . "/mod/gis/gis_fns.inc";
include_once "lib_ims.inc";
include_once $global['approot'] . "/inc/lib_security/lib_acl.inc";
function _shn_ims_regform_inv($error = false) {
    global $global;
    //global $conf;
    $db = $global['db'];
?>
<h2><?php echo _('Add an Inventory') ?></h2>
<?php
    if (!empty($error)) display_errors();
?>
<div id="formcontainer">
<?php
    //shn_form_fopen("reg_inv_cr");
    shn_form_fopen("reg_inv_cr", null, array('req' => false));
    shn_form_hidden(array('seq' => 'img'));
    shn_form_fsopen(_('Primary Details'));
    $extra_opts['req'] = true;
    shn_form_text(_("Inventory Name : "), 'org_name', 'size="40"', $extra_opts);
    shn_form_fsclose();
    $parent = _shn_ims_get_start_loc();
    $range = array("start" => 1, "end" => 5);
    shn_form_fsopen(_("Location"));
    shn_location($range, $value = null, $parent = null, $extra_opts = null);
    shn_form_fsclose();
    shn_gis_add_marker_map_form();
    shn_form_fsopen(_("Contact Information"));
    _shn_ims_display_contact_person($error, true, null);
    shn_form_fsclose();
    shn_form_fsopen(_("Facilities Avaliable"));
    _shn_ims_display_org_facilities($error);
    shn_form_fsclose();
?>
<br />
<center>
<?php
    //create the submit button
    // shn_form_hidden(array('range'=>$range));
    shn_form_submit(_("Next"));
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
    
}
function _shn_ims_regform_operation($error = false) {
    global $global;
    global $conf;
    $db = $global['db'];
?>
<h2><?php echo _("Add an Operation/Branch under the Inventory ") . $_SESSION["parent_name"] ?> </h2>
<?php
    if ($error) display_errors();
?>               
<div id="formcontainer">
<?php
    shn_form_fopen("reg_operation_cr");
    shn_form_fsopen('Primary Details');
    $extra_opts['req'] = true;
    shn_form_text(_("Operation/Branch Name : "), 'org_name', 'size="40"', $extra_opts);
    shn_form_fsclose();
    shn_form_fsopen(_("Inventory Sector"));
    _shn_ims_display_sector($error);
    shn_form_fsclose();
    // base location
    shn_form_fsopen(_("Base Location"));
    $parent = _shn_ims_get_start_loc();
    $range = shn_ims_get_loc_range();
    shn_location($range, $_POST[$range["end"]], $parent);
    shn_form_fsclose();
    shn_form_fsopen(_("Contact Information"));
    _shn_ims_display_contact_person($error, true, null);
    shn_form_fsclose();
    shn_form_fsopen(_("Facilities Avaliable"));
    _shn_ims_display_org_facilities($error);
    shn_form_fsclose();
    shn_form_fsopen(_("Extra Information"));
    _shn_ims_display_extra($error);
    shn_form_fsclose();
?>
<br />
<center>
<?php
    //create the submit button
    shn_form_submit(_("Next"));
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
?>     
</div>
<?php
    // end of form
    
}
?>
<?php
// end of form
function _shn_ims_validate_reg_inv() {
    $error_flag = false;
    $VARCHAR = 100;
    //$bsd_village=trim($_POST[$range["end"]]);
    //$end=trim($_POST[$range["end"]]);
    $inv_name = trim($_POST['org_name']);
    $contact_name = trim($_POST['contact_name']);
    $contact_add = trim($_POST['contact_add']);
    $contact_phone = trim($_POST['contact_phone']);
    $contact_mobile = trim($_POST['contact_mobile']);
    $contact_fax = trim($_POST['contact_fax']);
    $contact_mail = trim($_POST['contact_mail']);
    $contact_web = trim($_POST['contact_web']);
    $man_power = trim($_POST['man_power']);
    $equipment = trim($_POST['equipment']);
    $resources = trim($_POST['resources']);
    $space = trim($_POST['space']);
    if ($inv_name == null) {
        add_error(_("Inventory Name cannot be empty."));
        $error_flag = true;
    }
    global $global;
    $db = $global['db'];
    $q = "SELECT inventory_name FROM ims_inventory_records WHERE inventory_name='$inv_name'";
    $res = $db->Execute($q);
    if (!$res->EOF) {
        add_error(_("Inventory Name already exists."));
        $error_flag = true;
    }
    if (strlen($contact_name) > $VARCHAR) {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag = true;
    }
    if (strlen($contact_name) != 0 && shn_valid_name($contact_name)) {
        add_error(_('Invalid contact name'));
        $error_flag = true;
    }
    //$contact_address=$_POST['contact_add'];
    if (strlen($contact_phone) > $VARCHAR) {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag = true;
    }
    if (strlen($contact_phone) != 0 && shn_valid_phone2($contact_phone, 'contact phone number')) {
        $error_flag = true;
    }
    if (strlen($contact_mobile) > $VARCHAR) {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag = true;
    }
    if (strlen($contact_mobile) != 0 && shn_valid_phone2($contact_mobile, 'contact mobile number')) {
        $error_flag = true;
    }
    if (strlen($contact_fax) > $VARCHAR) {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag = true;
    }
    if (strlen($contact_fax) != 0 && shn_valid_phone2($contact_fax, 'contact fax number')) {
        $error_flag = true;
    }
    if (strlen($contact_mail) > $VARCHAR) {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag = true;
    }
    if (!shn_valid_email($contact_mail)) {
        add_error(SHN_ERR_or_ims_EMAIL);
        $error_flag = true;
    }
    if (strlen($contact_web) > $VARCHAR) {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag = true;
    }
    if (strlen($man_power) > $VARCHAR) {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag = true;
    }
    if (strlen($equipment) > $VARCHAR) {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag = true;
    }
    //$resources=$_POST['resources'];
    if (strlen($space) > $VARCHAR) {
        add_error(SHN_ERR_ims_SPACE);
        $error_flag = true;
    }
    return $error_flag;
}
?>