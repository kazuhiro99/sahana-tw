<?php
/**Processing functions(add ,edit,delete,ect) for Organizations of the Organization Registry
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/
function _shn_or_reg_org_cr() {
    global $global;
    include_once "reg_org.inc";
    // include_once $global['approot']."/inc/lib_security/authenticate.inc";
    include_once ($global['approot'] . "/inc/lib_uuid.inc");
    include_once $global['approot'] . "/mod/gis/gis_fns.inc";
    print $_SESSION['org']['name'];
    $db = $global['db'];
    $q = "select o_uuid from org_main where name='{$_SESSION['org']['name']}'";
    $res = $db->Execute($q);
    if (($res == NULL) || ($res->EOF)) {
        //return false;
        
    } else {
        if ($_SESSION['org']['same_name_confirm'] == false) {
            //shn_form_fopen("reg_org_name_change",null,array("name"=>"confirm_name","req_message"=>false));
            shn_form_fopen("reg_org_cr", null, array("name" => "confirm_name", "req_message" => false));
            $msg = _("There is already an Organization by the name ") . "<strong>" . $_SESSION['org']['name'] . "</strong>" . _(" you are trying to register ") . "<br />";
            $msg = $msg . _("From the below buttons ,Please Click ") . "<span style=\"color: brown;font-weight:bolder\">" . _("Continue") . "</span>" . " to continue with this name or Click <span style=\"color: green;font-weight:bolder\">" . _("Edit") . "</span>" . _(" to Change the Name") . "<br />";
            add_warning($msg);
            $extra_opts['br'] = false;
            $extra_opts['req'] = false;
            shn_form_fsopen(_('Continue with the existing name'));
            shn_form_button(_("Continue"), "onClick='change_action(\"continue\")'", $extra_opts);
            shn_form_fsclose();
            shn_form_fsopen(_('Change name'));
            shn_form_button(_("Edit"), "onClick='change_action(\"edit_name\")'", $extra_opts);
            shn_form_fsclose();
            shn_form_hidden(array('action' => '0'));
            _shn_or_action_change_javascript("confirm_name", "action");
            shn_form_fclose();
            return true;
        }
        //$_SESSION['org']['same_name_confirm']=false;
        
    }
    $org_id = shn_create_uuid('org');
    //  $org_id = $db->GenID('org_seq',1);
    if (empty($org_id)) {
        $error = true;
        //("add_org(): ORG_ID generation failed!");
        return false;
    }
    $q = "select o_uuid from org_main where o_uuid='{$org_id}'";
    $res = $db->Execute($q);
    if (!$res->EOF) {
        $error = true;
        add_error(SHN_ERR_OR_ORG_EXISTS);
        return false;
    }
    if ($error != true) {
        //no validation done on other fields as they are not unique
        $privacy = 0;
        $q = "insert into org_main(o_uuid,name,opt_org_type,reg_no,man_power,
        equipment,services,resources,privacy)
        values('{$org_id}','{$_SESSION['org']['name']}',
        '{$_SESSION['org']['type']}','{$_SESSION['org']['reg_no']}',
        '{$_SESSION['org']['man_power']}','{$_SESSION['org']['equipment']}',
        '" . implode(',', $_SESSION['org']['services']) . "',
        '{$_SESSION['org']['resources']}',$privacy)";
        $res = $db->Execute($q);
        $q = "insert into resource_to_incident(incident_id,x_uuid) values('{$_SESSION['user_pref_ims_incident_id']}','{$org_id}')";
        $res = $db->Execute($q);
        $i = 0;
        while ($i < count($_SESSION['org']['sector'])) {
            $q = "insert into sector(pgoc_uuid,opt_sector) values('{$org_id}','{$_SESSION['org']['sector'][$i]}')";
            $res = $db->Execute($q);
            $i = $i + 1;
        }
        $q = "insert into location_details(poc_uuid,location_id,address) values('{$org_id}','{$_SESSION['org']['loc']}','{$_SESSION['org']['loc_txt']}')";
        $res = $db->Execute($q);
        if ($_SESSION['org']['contact_address'] != null) {
            $q = "insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','loc_txt','{$_SESSION['org']['contact_address']}')";
            $res = $db->Execute($q);
        }
        if ($_SESSION['org']['contact_phone'] != null) {
            $q = "insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','curr','{$_SESSION['org']['contact_phone']}')";
            $res = $db->Execute($q);
        }
        if ($_SESSION['org']['contact_mobile'] != null) {
            $q = "insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','pmob','{$_SESSION['org']['contact_mobile']}')";
            $res = $db->Execute($q);
        }
        if ($_SESSION['org']['contact_name'] != null) {
            $q = "insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','name','{$_SESSION['org']['contact_name']}')";
            $res = $db->Execute($q);
        }
        if ($_SESSION['org']['contact_fax'] != null) {
            $q = "insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','fax','{$_SESSION['org']['contact_fax']}')";
            $res = $db->Execute($q);
        }
        if ($_SESSION['org']['contact_mail'] != null) {
            $q = "insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','email','{$_SESSION['org']['contact_mail']}')";
            $res = $db->Execute($q);
        }
        if ($_SESSION['org']['contact_web'] != null) {
            $q = "insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','web','{$_SESSION['org']['contact_web']}')";
            $res = $db->Execute($q);
        }
        shn_gis_dbinsert($org_id, 0, null, $_SESSION['org']['loc_x'], $_SESSION['org']['loc_y'], null);
    }
    if ($error != true) {
        $msg = $_SESSION['org']['name'] . _(" Organization was succesfully registered ");
        add_confirmation($msg);
        //$_SESSION['org']['same_name_confirm']=false;
        
?>
    <div id="result_msg">
    <?php
        $form_opts['name'] = 'confirm';
        $form_opts['req_message'] = false;
        shn_form_fopen("reg_org_finalize", null, $form_opts);
        $extra_opts['br'] = false;
        $extra_opts['req'] = false;
        $_SESSION['org']['parent_id'] = $org_id;
        shn_form_fsopen(_('Register a Branch/Department'));
        $msg = _("Now you can add a Branch/Department Under ") . "<strong>" . $_SESSION['org']['name'] . "</strong><br />" . _("e.g. Health Department,Relief Operations Department. : ") . "<br />";
        $msg = $msg . _("Of course you can add Branches/Departments later on through the Register a Department/Branch link.") . "<br />";
?><div class="info"><?php echo $msg ?></div><br /><?php
        shn_form_button(_("Register a Branch/Department"), "onClick='change_action(\"operation\")'", $extra_opts);
        shn_form_fsclose();
        shn_form_fsopen(_('Register another Organization'));
        $msg = _("Instead if you wish to add another organization click the button below ") . "<br />";
?><div class="info"><?php echo $msg ?></div><br /><?php
        shn_form_button(_("Register an Organization"), "onClick='change_action(\"org\")'", $extra_opts);
        shn_form_fsclose();
        shn_form_hidden(array('action' => '0'));
        shn_form_hidden(array('org_id' => $org_id));
        _shn_or_action_change_javascript("confirm", "action");
?>
</center>
<br />
<?php
        //close the form
        shn_form_fclose(false);
    }
}
function _shn_or_reg_operation_cr() {
    global $global;
    include_once "reg_org.inc";
    include_once ($global['approot'] . "/inc/lib_uuid.inc");
    include_once $global['approot'] . "/mod/gis/gis_fns.inc";
    if ($_SESSION['org'] != null) {
        $db = $global['db'];
        $org_id = shn_create_uuid('org');
        //  $org_id = $db->GenID('org_seq',1);
        if (empty($org_id)) {
            $error = true;
            //("add_org(): ORG_ID generation failed!");
            return false;
        }
        $q = "SELECT o_uuid FROM org_main WHERE o_uuid='{$org_id}'";
        $res = $db->Execute($q);
        if (!$res->EOF) {
            $error = true;
            add_error(SHN_ERR_OR_ORG_EXISTS);
            return false;
        }
        if ($error != true) {
            //no validation done on other fields as they are not unique
            $privacy = 0;
            $q = "INSERT INTO org_main(o_uuid,parent_id,name,opt_org_type,
            reg_no,man_power,equipment,services,resources,privacy)
            VALUES('{$org_id}','{$_SESSION['org']['parent_id']}',
            '{$_SESSION['org']['name']}','{$_SESSION['org']['type']}',
            '{$_SESSION['org']['reg_no']}','{$_SESSION['org']['man_power']}',
            '{$_SESSION['org']['equipment']}',
            '" . implode(',', $_SESSION['org']['services']) . "',
            '{$_SESSION['org']['resources']}',$privacy)";
            $res = $db->Execute($q);
            $q = "INSERT INTO resource_to_incident(incident_id,x_uuid) VALUES('{$_SESSION['user_pref_ims_incident_id']}','{$org_id}')";
            $res = $db->Execute($q);
            $i = 0;
            while ($i < count($_SESSION['org']['sector'])) {
                $q = "INSERT INTO sector(pgoc_uuid,opt_sector) VALUES('{$org_id}','{$_SESSION['org']['sector'][$i]}')";
                $res = $db->Execute($q);
                $i = $i + 1;
            }
            $q = "INSERT INTO location_details(poc_uuid,location_id,address) VALUES('{$org_id}','{$_SESSION['org']['loc']}','{$_SESSION['org']['loc_txt']}')";
            $res = $db->Execute($q);
            if ($_SESSION['org']['contact_phone'] != null) {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','curr','{$_SESSION['org']['contact_phone']}')";
                $res = $db->Execute($q);
            }
            if ($_SESSION['org']['contact_mobile'] != null) {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','pmob','{$_SESSION['org']['contact_mobile']}')";
                $res = $db->Execute($q);
            }
            if ($_SESSION['org']['contact_name'] != null) {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','name','{$_SESSION['org']['contact_name']}')";
                $res = $db->Execute($q);
            }
            if ($_SESSION['org']['contact_fax'] != null) {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','fax','{$_SESSION['org']['contact_fax']}')";
                $res = $db->Execute($q);
            }
            if ($_SESSION['org']['contact_mail'] != null) {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','email','{$_SESSION['org']['contact_mail']}')";
                $res = $db->Execute($q);
            }
            if ($_SESSION['org']['contact_web'] != null) {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','web','{$_SESSION['org']['contact_web']}')";
                $res = $db->Execute($q);
            }
            shn_gis_dbinsert($org_id, 0, null, $_SESSION['org']['loc_x'], $_SESSION['org']['loc_y'], null);
        }
        if ($error != true) {
            $msg = $_SESSION['org']['name'] . _(" Organization was succesfully registered ");
            add_confirmation($msg);
            unset($_SESSION['org']);
        }
    }
    /*
    include_once "reg_org.inc";
    include_once "errors.inc";
    global $global;
    include_once $global['approot']."/inc/lib_validate.inc";
    include_once($global['approot']."/inc/lib_uuid.inc");
    $error=false;
    $VARCHAR=100;
    $parent_id=$_POST["parent"];
    list($error,$org_name)=(shn_validate_field($_POST['org_name'],"Organization Name",$VARCHAR,true))?array($error,$_POST['org_name']):array(true,NULL);
    list($error,$opt_org_sub_type)=(shn_validate_opt_field('opt_org_sub_type',$_POST['opt_org_sub_type'],"Relationship to the parent organization",$VARCHAR,false))?array($error,$_POST['opt_org_sub_type']):array(true,NULL);
    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST['opt_sector_type'],"Organization Sector",$VARCHAR,true))?array($error,$_POST['opt_sector_type']):array(true,NULL);
    
    
    $loc=shn_location_get_form_submit_loc();
    if($loc==-1){
    add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    $error=true;
    }
    
    $contact_name=$_POST['contact_name'];
    $contact_address=$_POST['contact_add'];
    $contact_phone=$_POST['contact_phone'];
    $contact_mobile=$_POST['contact_mobile'];
    $contact_fax=$_POST['contact_fax'];
    if (trim(strlen($_POST['contact_mail'])) > $VARCHAR){
    add_error(SHN_ERR_OR_REG_MAX);
    $error=true;
    }else {
    $contact_mail=$_POST['contact_mail'];
    if(!shn_valid_email($contact_mail)){
    add_error(SHN_ERR_OR_EMAIL);
    $error=true;
    }
    }
    $contact_web=$_POST['contact_web'];
    $man_power=$_POST['man_power'];
    $equipment=$_POST['equipment'];
    $resources=$_POST['resources'];
    $chk_branch=(isset ($_POST['chk_branch']))?1:0;
    $db=$global['db'];
    $org_id	=shn_create_uuid('org');;
    if (empty($org_id)){
    return false;
    }
    $q="select o_uuid from org_main where o_uuid='{$org_id}'";
    $res=$db->Execute($q);
    if(!$res->EOF){
    $error=true;
    add_error(SHN_ERR_OR_ORG_EXISTS);
    }
    if(!$error){
    
    //no validation done on other fields as they are not unique
    $q="insert into org_main(o_uuid,parent_id,name,opt_org_type,man_power,equipment,resources)values('{$org_id}','{$parent_id}','{$org_name}','{$opt_org_sub_type}','{$man_power}','{$equipment}','{$resources}')";
    $res=$db->Execute($q);
    $q="insert into resource_to_incident(incident_id,x_uuid) values('{$_SESSION['user_pref_ims_incident_id']}','{$org_id}')";
    $res=$db->Execute($q);
    $i=0;
    while($i<count($sector)){
    $q="insert into sector(pgoc_uuid,opt_sector) values('{$org_id}','{$sector[$i]}')";
    $res=$db->Execute($q);
    $i=$i+1;
    }
    }
    $q="insert into location_details(poc_uuid,location_id,address) values('{$org_id}','{$loc}','{$contact_address}')";
    $res=$db->Execute($q);
    if($contact_name!=null){
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','name','{$contact_name}')";
    $res=$db->Execute($q);
    }
    if($contact_phone!=null){
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','curr','{$contact_phone}')";
    $res=$db->Execute($q);
    }
    if($contact_mobile!=null){
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','pmob','{$contact_mobile}')";
    $res=$db->Execute($q);
    }
    if($contact_fax!=null){
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','fax','{$contact_fax}')";
    $res=$db->Execute($q);
    }
    if($contact_mail!=null){
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','email','{$contact_mail}')";
    $res=$db->Execute($q);
    }
    if($contact_web!=null){
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$org_id}','web','{$contact_web}')";
    $res=$db->Execute($q);
    }
    if(!$error){
    $msg= $org_name." Operation/Branch was succesfully registered ";
    add_confirmation($msg);
    ?>
    <br />
    <?php
    }
    _shn_or_regform_operation($error);
    
    
    */
}

function _shn_or_del_org_validate() {
    global $global;
    $db = $global['db'];
    $org_id = $_POST['org_id'];
    $sql = "SELECT * FROM org_main WHERE parent_id = '$org_id'";
    $res = $db->GetOne($sql);
    if ($res) {
        return false;
    }
    else {
        return true;
    }
}

function _shn_or_del_org() {
    global $global;
    $db = $global['db'];
    $org_id = $_POST['org_id'];
    $q = "SELECT name FROM org_main WHERE o_uuid='{$org_id}'";
    $res = $db->Execute($q);
    $org_name = $res->fields["name"];
    $q = "DELETE FROM org_main WHERE o_uuid='{$org_id}'";
    $res = $db->Execute($q);
    $q = "DELETE FROM sector WHERE pgoc_uuid='{$org_id}'";
    $res = $db->Execute($q);
    $q = "DELETE FROM location_details WHERE poc_uuid='{$org_id}'";
    $res = $db->Execute($q);
    $q = "DELETE FROM contact WHERE pgoc_uuid='{$org_id}'";
    $res = $db->Execute($q);
    /*
    if($error==true){
    _shn_or_viewform_org($org_id,$error);
    return false;
    }
    */
    $msg = $org_name . _(" was succesfully deleted ");
    add_confirmation($msg);
?>

    <br />
<?php
    shn_or_view_org();
}
function _shn_or_edit_org() {
    global $global;
    include_once "errors.inc";
    include_once "lib_or.inc";
    include_once $global['approot'] . "/inc/lib_validate.inc";
    //$incidents=$_POST["incidents"];
    $error = false;
    $VARCHAR = 100;
    $org_id = $_SESSION['org']['org_id'];
    $parent = _shn_or_is_root($org_id);
    if ($parent) {
        $type = "opt_org_type";
    } else {
        $type = "opt_org_sub_type";
    }
    list($error, $org_name) = (shn_validate_field($_SESSION['org']['name'], "Organization Name", $VARCHAR, true)) ? array($error, $_SESSION['org']['name']) : array(true, NULL);
    list($error, $org_type) = (shn_validate_opt_field($type, $_SESSION['org']['type'], "Organization Type", $VARCHAR, false)) ? array($error, $_SESSION['org']['type']) : array(true, NULL);
    list($error, $sector) = (shn_validate_opt_field('opt_sector_type', $_SESSION['org']['sector'], "Organization Sector", $VARCHAR, true)) ? array($error, $_SESSION['org']['sector']) : array(true, NULL);
    $loc = shn_location_get_form_submit_loc();
    $loc = (isset($loc) && $loc > - 1) ? $loc : isset($_SESSION['org']['loc']) ? $_SESSION['org']['loc'] : -1;
    $lat = $_SESSION['org']['gps_x'];
    $lon = $_SESSION['org']['gps_y'];
    if (trim(strlen($_SESSION['org']['reg_no'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $reg_no = $_SESSION['org']['reg_no'];
    }
    if (trim(strlen($_SESSION['org']['loc_txt'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $loc_txt = $_SESSION['org']['loc_txt'];
    }
    if (trim(strlen($_SESSION['org']['contact_name'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $contact_name = $_SESSION['org']['contact_name'];
    }
    /*
    if (trim(strlen($_POST['contact_add'])) > $CONTACT_ADDRESS){
    add_error(SHN_ERR_OR_REG_MAX);
    }else {
    $contact_address=$_POST['contact_add'];
    }
    */
    $contact_address = $_SESSION['org']['contact_address'];
    if (trim(strlen($_SESSION['org']['contact_phone'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $contact_phone = $_SESSION['org']['contact_phone'];
    }
    if (trim(strlen($_SESSION['org']['contact_mobile'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $contact_mobile = $_SESSION['org']['contact_mobile'];
    }
    if (trim(strlen($_SESSION['org']['contact_fax'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $contact_fax = $_SESSION['org']['contact_fax'];
    }
    if (trim(strlen($_SESSION['org']['contact_mail'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $contact_mail = $_SESSION['org']['contact_mail'];
        if (!shn_valid_email($contact_mail)) {
            add_error(SHN_ERR_OR_EMAIL);
            $error = true;
        }
    }
    if (trim(strlen($_SESSION['org']['contact_web'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $contact_web = $_SESSION['org']['contact_web'];
    }
    if (trim(strlen($_SESSION['org']['man_power'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $man_power = $_SESSION['org']['man_power'];
    }
    if (trim(strlen($_SESSION['org']['equipment'])) > $VARCHAR) {
        add_error(SHN_ERR_OR_REG_MAX);
        $error = true;
    } else {
        $equipment = $_SESSION['org']['equipment'];
    }
    $resources = $_SESSION['org']['resources'];
    if (!$error) {
        $db = $global['db'];
        //no validation done on other fields as they are not unique
        $q = "UPDATE org_main SET name='{$org_name}',
        opt_org_type='{$org_type}',reg_no='{$reg_no}',
        man_power='{$man_power}', equipment='{$equipment}',
        services='" . implode(',', $_SESSION['org']['services']) . "',
        resources='{$resources}'
        where o_uuid='{$org_id}'";
        $res = $db->Execute($q);
        $q = "DELETE FROM sector WHERE pgoc_uuid='{$org_id}'";
        $res = $db->Execute($q);
        $i = 0;
        while ($i < count($sector)) {
            $q = "INSERT INTO sector(pgoc_uuid,opt_sector) VALUES('{$org_id}','{$sector[$i]}')";
            $res = $db->Execute($q);
            $i = $i + 1;
        }
        /*
        $q="delete from resource_to_incident where x_uuid='{$org_id}'";
        $res=$db->Execute($q);
        $i=0;
        
        while($i<count($incidents)){
        $q="insert into resource_to_incident(incident_id,x_uuid) values($incidents[$i],'{$org_id}')";
        $res=$db->Execute($q);
        $i=$i+1;
        }
        */
        // if($loc!=-1){
        $q = "UPDATE location_details SET location_id='{$loc}',address='{$loc_txt}' WHERE poc_uuid='{$org_id}'";
        $res = $db->Execute($q);
        //}
        $q = "UPDATE gis_location SET map_northing={$lat},map_easting={$lon} WHERE poc_uuid='{$org_id}'";
        $res = $db->Execute($q);
        if ($contact_address != null) {
            if (shn_or_contact_data_exist($org_id, 'loc_txt') == true) {
                $q = "UPDATE contact SET contact_value='{$contact_address}' WHERE pgoc_uuid='{$org_id}' and opt_contact_type='loc_txt'";
            } else {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','loc_txt','{$contact_address}')";
            }
            $res = $db->Execute($q);
        }
        if ($contact_name != null) {
            if (shn_or_contact_data_exist($org_id, 'name') == true) {
                $q = "UPDATE contact SET contact_value='{$contact_name}' WHERE pgoc_uuid='{$org_id}' and opt_contact_type='name'";
            } else {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','name','{$contact_name}')";
            }
            $res = $db->Execute($q);
        }
        if ($contact_phone != null) {
            if (shn_or_contact_data_exist($org_id, 'curr') == true) {
                $q = "UPDATE contact SET contact_value='{$contact_phone}' WHERE pgoc_uuid='{$org_id}' and opt_contact_type='curr'";
            } else {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','curr','{$contact_phone}')";
            }
            $res = $db->Execute($q);
        }
        if ($contact_mobile != null) {
            if (shn_or_contact_data_exist($org_id, 'pmob') == true) {
                $q = "UPDATE contact set contact_value='{$contact_mobile}' WHERE pgoc_uuid='{$org_id}' and opt_contact_type='pmob'";
            } else {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','pmob','{$contact_mobile}')";
            }
            $res = $db->Execute($q);
        }
        if ($contact_fax != null) {
            if (shn_or_contact_data_exist($org_id, 'fax') == true) {
                $q = "UPDATE contact SET contact_value='{$contact_fax}' WHERE pgoc_uuid='{$org_id}' and opt_contact_type='fax'";
            } else {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','fax','{$contact_fax}')";
            }
            $res = $db->Execute($q);
        }
        if ($contact_mail != null) {
            if (shn_or_contact_data_exist($org_id, 'email') == true) {
                $q = "UPDATE contact SET contact_value='{$contact_mail}' WHERE pgoc_uuid='{$org_id}' and opt_contact_type='email'";
            } else {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','email','{$contact_mail}')";
            }
            $res = $db->Execute($q);
        }
        if ($contact_web != null) {
            if (shn_or_contact_data_exist($org_id, 'web') == true) {
                $q = "UPDATE contact SET contact_value='{$contact_web}' WHERE pgoc_uuid='{$org_id}' and opt_contact_type='web'";
            } else {
                $q = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','web','{$contact_web}')";
            }
            $res = $db->Execute($q);
        }
        $msg = $org_name . _(" was succesfully updated ");
        add_confirmation($msg);
?>

    <br />

<?php
    }
    if (!empty($error)) {
        _shn_or_viewform_org($org_id, $error);
        return false;
    }
    //_shn_or_viewform_allorg();
    shn_or_view_org();
}
?>
