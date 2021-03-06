<?php
/* $Id: edit.inc,v 1.26.2.19 2008/07/25 06:31:07 ravithb Exp $ */
/**Update functions for  CR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @subpackage cr
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @author   Mifan Careem <mifan@opensource.lk>
* @edited by Isuru Samaraweera <isuru@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/
include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');
include_once ($global['approot'] . '/inc/lib_errors.inc');
include_once $global['approot'] . "/inc/lib_location.inc";
global $editid;
function _shn_cr_cedt_start($errors = false) {
    if ($errors) display_errors();
    global $global, $range, $conf;
    $db = $global['db'];
?>
<h2><?php echo _("Update Existing Shelter"); ?></h2>
	<?php
    $editid = $_REQUEST['cmp_id'];
    $_SESSION['editid'] = $editid;
    _shn_cr_get_session($editid);
    shn_form_fopen('ecmp');
    shn_form_fsopen(_("General Details"));
    shn_form_hidden(array('seq' => 'chk'));
    shn_form_hidden(array('cmp_id' => $_SESSION['editid']));
    shn_form_text(_("Shelter Name"), "camp_name", 'size="50"', array('req' => true, 'value' => $_SESSION['camp_name']));
    shn_form_opt_select("opt_camp_type", _("Shelter Type"), null, array('value' => $_SESSION['opt_camp_type']));
    shn_form_textarea(_("Address"), "camp_address", null, array('value' => $_SESSION['camp_address']));
    shn_form_fsclose();
    shn_form_fsopen(_("Location Details"));
    shn_location($range, $_SESSION['opt_location_type']);
    shn_form_fsclose();
    shn_form_fsopen(_("Map Location"));
    echo '<div class=\'message information\'>';
    echo _('Click on the button "Update the location" will update the map location if you did manually modify the values of position.');
    echo "</div>";
    $extra_opts['req'] = false;
    $extra_opts['value'] = $_SESSION['camp_lat'];
    shn_form_text(_("Latitude : "), 'gps_x', 'size="40"', $extra_opts);
    $extra_opts['value'] = $_SESSION['camp_lon'];
    shn_form_text(_("Longitude : "), 'gps_y', 'size="40"', $extra_opts);
    shn_form_button(_('Update the location'));
    shn_form_fsclose();
    if ($conf['gis']) {
        $extra_opts['marker'] = 'single';
        shn_form_fsopen($name_of_map);
        $plugin_name = $conf['mod_gis_dflt'];
        include $global['approot'] . "/mod/gis/plugins/" . "$plugin_name" . "/handler_" . "$plugin_name" . ".inc";
        echo "<div class='message information'>";
        echo _("You can move around and enlarge/reduce the size of the area you want using
the scale on upper left corner of the map. By clicking on a map you can
mark your location with a pointer.");
        echo "</div>";
        show_add_marker_map($nameOfPoint, $extra_opts);
        shn_form_fsclose();
    }
    //-----------------------------------------
    shn_form_fsopen(_("Contact Person Details"));
    shn_form_text(_("Full Name"), "camp_contact_name", 'size="60"', array('value' => $_SESSION['camp_contact_name']));
    shn_form_text(_("Phone Number"), "camp_contact_number", 'size="60"', array('value' => $_SESSION['camp_contact_number']));
    shn_form_text(_("Mobile Number"), "contact_mob", 'size="60"', array('value' => $_SESSION['camp_contact_mob']));
    shn_form_text(_("Occupation"), "occupation", 'size="60"', array('value' => $_SESSION['camp_occupation']));
    shn_form_fsclose();
    shn_form_fsopen(_("Shelter Population"));
    shn_form_text(_("Capacity"), "capacity", 'size="10"', array('value' => $_SESSION['camp_capacity']));
    shn_form_text(_("Men"), "men", 'size="10"', array('value' => $_SESSION['camp_men']));
    shn_form_text(_("Women"), "women", 'size="10"', array('value' => $_SESSION['camp_women']));
    shn_form_text(_("Children( 1 ~ 12 years old )"), "children", 'size="10"', array('value' => $_SESSION['camp_children']));
    echo '<hr />';
    shn_form_text(_("Infected Count"), "family", 'size="10"', array('value' => $_SESSION['camp_family']));
    shn_form_date(_('Update time'), 'modified', array(
        'value' => $_SESSION['camp_modified']
    ));
    shn_form_fsclose();
    shn_form_submit(_("Next"));
    shn_form_fclose();
}
function shn_cr_all_view() {
?>
<script type="text/javascript">
	function editThis(){
		var x=window.confirm('<?php echo _("Do You Really Want to Delete?") ?>');
		if (x){
			return true;
		}else{
			return false;
		}
	}
</script>
	<?php
    global $global;
    $db = $global['db'];
?>
<h2><?php echo _("Shelter Details") ?></h2>
	<?php
    /*$query="select c_uuid from camp_general where name='{$_REQUEST['cmp_id']}'";
    $res=$db->Execute($query);
    $editid=$res->fields[0];*/
    $editid = $_REQUEST['cmp_id'];
    $_SESSION['editid'] = $editid;
    _shn_cr_get_session($editid);
    shn_form_fopen('crch');
    shn_form_fsopen(_("General Details"));
    shn_form_hidden(array('seq' => 'show'));
    $sql = "SELECT option_description FROM field_options WHERE field_name = 'opt_camp_type' AND option_code = '{$_SESSION['opt_camp_type']}'";
    $res = $global['db']->Execute($sql);
    $_SESSION['camp_type'] = '';
    if ($res->RecordCount() > 0) {
        $_SESSION['camp_type'] = $res->fields['option_description'];
    }
    shn_form_hidden(array('opt_camp_type' => $_SESSION['opt_camp_type']));
    shn_form_label(_("Shelter Name"), $_SESSION['camp_name'], array('br' => 'true'));
    shn_form_label(_("Shelter Type"), $_SESSION['camp_type'], array('br' => 'true'));
?>
<!--
<label>Division</label>
<select name="opt_location_type" >-->
	<?php
    // Display selected Division type only
    /*
    $q="select value from config where confkey='division_type' && module_id='cr'";
    //$q ="select option_description from field_options where field_name='cr_pref_div'";
    $ref = $db->Execute($q);
    $val=$ref->fields[0];
    $q ="select location_id,name from location where opt_location_type=$val";
    $ref = $db->Execute($q);
    while(!$ref->EOF){
    $val=$ref->fields[0];
    $name=$ref->fields[1];
    ?>
    <option value='<?=$val?>'><?=$name?></option>
    <?php
    $ref->MoveNext();
    }
    */
?>
<!--</select><br>-->
	<?php
    global $global;
    include $global['approot'] . "/mod/or/lib_or.inc";
    //-----------------------------------------
    shn_form_label(_("Address"), $_SESSION['camp_address']);
    $leaf = $_SESSION['opt_location_type'];
    $sql = 'SELECT location.name, location.parent_id, field_options.option_description
            FROM location
            INNER JOIN field_options ON field_options.option_code = location.opt_location_type
            WHERE location.loc_uuid = \'%s\'';
    $counter = 0;
    $result = array(
        'parent_id' => '1'
    );
    while(!empty($result['parent_id'])) {
        $result = $global['db']->GetRow(sprintf($sql, $leaf));
        if(!empty($result)) {
            shn_form_label($result['option_description'], $result['name']);
            $leaf = $result['parent_id'];
        }
    }
    shn_form_fsclose();
    //shn_location_form_view(1,4,$_SESSION['opt_location_type']);
    shn_form_fsopen(_("Contact Person Details"));
    shn_form_label(_("Full Name"), $_SESSION['camp_contact_name']);
    shn_form_label(_("Phone Number"), $_SESSION['camp_contact_number']);
    shn_form_label(_("Mobile Number"), $_SESSION['camp_contact_mob']);
    shn_form_label(_("Occupation"), $_SESSION['camp_occupation']);
    shn_form_fsclose();
    shn_form_fsopen(_("Shelter Population"));
    shn_form_label(_("Capacity"), $_SESSION['camp_capacity']);
    shn_form_label(_("Men"), $_SESSION['camp_men']);
    shn_form_label(_("Women"), $_SESSION['camp_women']);
    shn_form_label(_("Children( 1 ~ 12 years old )"), $_SESSION['camp_children']);
    shn_form_label(_("Total Count") . " : ", $_SESSION['camp_total']);
    echo '<hr />';
    shn_form_label(_("Infected Count"), $_SESSION['camp_family']);
    shn_form_label(_('Update time'), $_SESSION['camp_modified']);
    shn_form_fsclose();
    $sql = "SELECT option_description FROM field_options WHERE option_code IN (SELECT opt_camp_service FROM camp_services WHERE c_uuid = '{$_SESSION['editid']}') AND field_name = 'opt_camp_service'";
    $res = $global['db']->Execute($sql);
    if ($res->RecordCount() > 0) {
        shn_form_fsopen(_('Available services'));
        for ($i = 0;$i < $res->RecordCount();$i++) {
            shn_form_label('', $res->fields['option_description']);
            $res->MoveNext();
        }
        shn_form_fsclose();
    }
    shn_form_submit(_("Close"));
?>
<input type="button" onClick="location.replace('index.php?mod=cr&act=ecmp&seq=disp&cmp_id=<?php echo $_REQUEST['cmp_id'] ?>');" value=<?php echo _("Edit") ?> />
<input type="button" onClick="if(editThis()) location.replace('index.php?mod=cr&act=ecmp&seq=del&cmp_id=<?php echo $_SESSION['editid'] ?>');" value=<?php echo _("Delete") ?> />
	<?php
    shn_form_fclose();
}
function _shn_cr_cedt_chk($errors = false) {
    if ($errors) display_errors;
    global $global;
    include_once $global['approot'] . "/inc/lib_location.inc";
    $_SESSION['cr']['loc'] = shn_location_get_form_submit_loc();
    $_SESSION['camp_name'] = $_POST['camp_name'];
    $_SESSION['opt_camp_type'] = $_POST['opt_camp_type'];
    $_SESSION['opt_location_type'] = $_POST['opt_location_type'];
    $_SESSION['camp_address'] = $_POST['camp_address'];
    $_SESSION['camp_contact_name'] = $_POST['camp_contact_name'];
    $_SESSION['camp_contact_number'] = $_POST['camp_contact_number'];
    $_SESSION['camp_contact_mob'] = $_POST['contact_mob'];
    $_SESSION['camp_occupation'] = $_POST['occupation'];
    $_SESSION['camp_family'] = $_POST['family'];
    $_SESSION['camp_capacity'] = $_POST['capacity'];
    $_SESSION['camp_men'] = $_POST['men'];
    $_SESSION['camp_women'] = $_POST['women'];
    $_SESSION['camp_children'] = $_POST['children'];
    $_SESSION['camp_total'] = $_SESSION['camp_men']
        + $_SESSION['camp_women'] + $_SESSION['camp_children'];
    $_SESSION['camp_modified'] = $_POST['modified'];
    $_SESSION['cr_loc'] = shn_location_get_form_submit_loc();
    $_SESSION['camp_lat'] = $_POST['gps_x'];
    $_SESSION['camp_lon'] = $_POST['gps_y'];
    
?>
<h2><?=("Shelter Checklist") ?></h2>
	<?php
    shn_form_fopen("ecmp", '', array('req_message' => false));
    shn_form_fsopen(_("Services / Facilities Available"));
    shn_form_hidden(array('seq' => 'confir'));
    $db = $global['db'];
    $query = "select opt_camp_service from camp_services where c_uuid='{$_SESSION['editid']}'";
    $res = $db->Execute($query);
    $select = array();
    while (!$res->EOF) {
        array_push($select, $res->fields['opt_camp_service']);
        $res->MoveNext();
    }
    shn_form_opt_checkbox("opt_camp_service", array('selected' => $select));
    // 	shn_form_textarea(_("Other Facilities"),"comments");
    shn_form_fsclose();
    shn_form_submit(_("Next"));
    shn_form_fclose();
}
function _shn_cr_del_camp($id) {
    global $global;
    $db = $global['db'];
    $q = "delete from camp_general where c_uuid='{$id}'";
    $r = "delete from camp_reg where c_uuid='{$id}'";
    $s = "delete from camp_services where c_uuid='{$id}'";
    $db->Execute($q);
    $db->Execute($r);
    $db->Execute($s);
    add_confirmation(_("Deleted Shelter Succesfully"));
    //shn_cr_crch
    
}
function _shn_cr_cadd_commit() {
    global $global;
    //write to database
    $_SESSION['opt_camp_service'] = $_POST['opt_camp_service'];
    $_SESSION['camp_comments'] = $_POST['comments'];
    foreach($_SESSION['opt_camp_service'] as $a => $b) {
        //echo "value is $b";
        
    }
    //echo microtime(true);
    //var_dump($_SESSION);
    _shn_cr_cadd_commit_db();
}
function _shn_cr_create_cid() {
    //create unique camp id
    //db->GenID();
    $id = time();
    return $id;
}
function _shn_cr_search_edt_frm() {
?><h2 align="center">Edit Existing Shelter</h2><?php
    shn_form_fopen("ecmp");
    shn_form_fsopen(_("Edit Shelter"));
    shn_form_hidden(array('seq' => 'disp'));
    shn_form_text(_("Name of Shelter to edit"), 'cmp_id', 'size="20"');
    shn_form_fsclose();
    shn_form_submit(_("Edit"));
    shn_form_fclose();
}
function shn_cr_edt_srch() {
    global $global;
    include ($global['approot'] . '/mod/cr/search.inc');
    _shn_cr_srch(true);
}
function _shn_cr_validate_error() {
    clean_errors();
    $error_flag = false;
    if (null == ($_POST['camp_name'])) {
        add_error(_("Please enter the shelter  name"));
        $error_flag = true;
    }
    if (!(null == ($_POST['family']))) {
        if (!is_numeric(trim($_POST['family']))) {
            add_error(_("The infected count is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['family'])) {
            add_error(_("The infected count cannot be negative"));
            $error_flag = true;
        }
    }
    if (!(null == ($_POST['capacity']))) {
        if (!is_numeric(trim($_POST['capacity']))) {
            add_error(_("The capacity is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['capacity'])) {
            add_error(_("The capacity cannot be negative"));
            $error_flag = true;
        }
    }
    if (!(null == ($_POST['men']))) {
        if (!is_numeric(trim($_POST['men']))) {
            add_error(_("The men count is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['men'])) {
            add_error(_("The men count cannot be negative"));
            $error_flag = true;
        }
    }
    if (!(null == ($_POST['women']))) {
        if (!is_numeric(trim($_POST['women']))) {
            add_error(_("The women count is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['women'])) {
            add_error(_("The women count cannot be negative"));
            $error_flag = true;
        }
    }
    if (!(null == ($_POST['children']))) {
        if (!is_numeric(trim($_POST['children']))) {
            add_error(_("The children count is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['children'])) {
            add_error(_("The children count cannot be negative"));
            $error_flag = true;
        }
    }
    if ($_POST['children'] != null || $_POST['women'] != null || $_POST['men'] != null) {
        $totalcount = $_POST['children'] + $_POST['women'] + $_POST['men'];
        if ($_POST['family'] > $totalcount) {
            add_error("The Infected count should be less or equal than the total count");
            $error_flag = true;
        }
        if($_POST['capacity'] < $totalcount) {
            add_error(_('The capacity should be greater or equal than the total count'));
            $error_flag = true;
        }
    }
    return $error_flag;
}
function positive_number($nr) {
    if (ereg("^[0-9]+$", $nr) && $nr > - 1) {
        return true;
    } else {
        return false;
    }
}
/**
 * populate session variables from database
 * @param camp_id	the retrieved camp id
 */
function _shn_cr_get_session($camp_id) {
    global $global;
    $db = $global['db'];
    $query = "SELECT a.name,a.location_id,a.opt_camp_type,a.address,
    a.capacity,b.admin_name,b.admin_no,b.family,b.total,b.men,b.women,
    b.children,b.modified FROM camp_general AS a
    LEFT OUTER JOIN camp_reg AS b ON a.c_uuid=b.c_uuid
    WHERE a.c_uuid='{$camp_id}'";
    $res = $db->Execute($query);
    $_SESSION['camp_name'] = $res->fields['name'];
    $_SESSION['opt_camp_type'] = $res->fields['opt_camp_type'];
    $_SESSION['opt_location_type'] = $res->fields['location_id'];
    $_SESSION['camp_address'] = $res->fields['address'];
    $_SESSION['camp_contact_name'] = $res->fields['admin_name'];
    $_SESSION['camp_contact_number'] = $res->fields['admin_no'];
    $_SESSION['camp_family'] = $res->fields['family'];
    $_SESSION['camp_men'] = $res->fields['men'];
    $_SESSION['camp_women'] = $res->fields['women'];
    $_SESSION['camp_children'] = $res->fields['children'];
    $_SESSION['camp_total'] = $res->fields['total'];
    $_SESSION['camp_capacity'] = $res->fields['capacity'];
    $_SESSION['camp_modified'] = $res->fields['modified'];
    $query = "SELECT * FROM contact WHERE pgoc_uuid=(SELECT contact_puuid FROM camp_admin WHERE c_uuid='{$camp_id}')";
    $res = $db->Execute($query);
    $_SESSION['camp_contact_mob'] = $res->fields['contact_value'];
    $query = "SELECT occupation FROM person_details WHERE p_uuid=(SELECT contact_puuid FROM camp_admin WHERE c_uuid='{$camp_id}');";
    $res = $db->Execute($query);
    $_SESSION['camp_occupation'] = $res->fields['occupation'];
    $query = "SELECT map_northing, map_easting FROM gis_location WHERE poc_uuid='$camp_id';";
    $res = $db->Execute($query);
    $_SESSION['camp_lat'] = $res->fields["map_northing"];
    $_SESSION['camp_lon'] = $res->fields["map_easting"];
}
function _shn_cr_get_locid() {
    if ($_SESSION['cr_5'] != null) return $_SESSION['cr_5'];
    else if ($_SESSION['cr_4'] != null) return $_SESSION['cr_4'];
    else if ($_SESSION['cr_3'] != null) return $_SESSION['cr_3'];
    else if ($_SESSION['cr_2'] != null) return $_SESSION['cr_2'];
    else return $_SESSION['cr_1'];
}
function _shn_cr_cedt_commit() {
    if (isset($_POST['finish'])) {
        //insert to database;
        global $global;
        global $editid;
        $db = $global['db'];
        $admin = "SELECT * from camp_admin  where c_uuid='{$_SESSION['editid']}'";
        $res_admin = $db->Execute($admin);
        $pid = $res_admin->fields['contact_puuid'];
        $loc_id = $_SESSION['cr_loc'];
        //call unique camp id
        //$uid=_shn_cr_create_cid();
        //enter into camp table
        $q = "update camp_general set name='{$_SESSION['camp_name']}',location_id='{$loc_id}',opt_camp_type='{$_SESSION['opt_camp_type']}',address='{$_SESSION['camp_address']}',capacity={$_SESSION['camp_capacity']} where c_uuid='{$_SESSION['editid']}'";
        $res = $db->Execute($q);
        //enter into camp_reg table
        $q = "update camp_reg set
        admin_name='{$_SESSION['camp_contact_name']}',
        admin_no='{$_SESSION['camp_contact_number']}',
        men='{$_SESSION['camp_men']}',
        women='{$_SESSION['camp_women']}',
        family={$_SESSION['camp_family']},
        children='{$_SESSION['camp_children']}',
        total={$_SESSION['camp_total']},
        modified='{$_SESSION['camp_modified']}'
        where c_uuid='{$_SESSION['editid']}'";
        $res = $db->Execute($q);
        $qb = "UPDATE person_details set occupation='{$_SESSION['camp_occupation']}' where p_uuid='$pid'";
        $resb = $db->Execute($qb);
        // insert into admin contact
        $qc = "UPDATE contact SET contact_value='{$_SESSION['camp_contact_mob']}' WHERE pgoc_uuid='{$pid}' AND opt_contact_type='cmob'";
        $resc = $db->Execute($qc);
        $q = "UPDATE gis_location SET map_northing={$_SESSION['camp_lat']},map_easting={$_SESSION['camp_lon']} WHERE poc_uuid='{$_SESSION['editid']}'";
        $res = $db->Execute($q);
        /*insert services into camp_services table
        //currently add checked values
        foreach($_SESSION['opt_camp_service'] as $a => $b){
        //currently add checked values.
        //$q = "update camp_services(c_uuid,opt_camp_service,value) values($editid,'{$b}',1)";
        $res = $db->Execute($q);
        }
        */
        $uid = $_SESSION['editid'];
        if (isset($_SESSION['opt_camp_service'])) {
            //Delete previous values and override with current ones:
            $del = "DELETE FROM camp_services WHERE c_uuid='{$uid}'";
            $res = $db->Execute($del);
            foreach($_SESSION['opt_camp_service'] as $a => $b) {
                //currently add checked values.
                $q = "insert into camp_services(c_uuid,opt_camp_service,value) values('{$uid}','{$b}',1)";
                $res = $db->Execute($q);
            }
        }
?>

<? add_confirmation(_("You have succesfully edited shelter ") . $_SESSION['camp_name']); ?>
<br />
<h3><?php echo _("The availability of Services & Facilities of the shelter are as follows") ?></h3>

	<div id="note" style="text-align: left;">
            <div><?php echo _('Add Shelter'); ?>:<?php
            echo sprintf(_('Please click %s to add another shelter.'),
                    '<a href="index.php?mod=cr&act=acmp"><b>' . _('Add Shelter') . '</b></a>');
            ?></div>
            <div><?php echo _('Edit Shelter'); ?>:<?php
            echo sprintf(_('To edit current shelter, please do a search with %s or %s first to find the shelter you would like to edit.'),
                    '<a href="index.php?mod=cr&act=srch"><b>' . _('Search by Name') . '</b></a>',
                    '<a href="index.php?mod=cr&act=srch_address"><b>' . _('Search by address') . '</b></a>');
            ?></div>
	</div>
<br/>
<?php
    } elseif (isset($_POST['edit'])) {
        _shn_cr_cedit_second();
    }
}
//added to confirm edit
function _shn_cr_cedit_confir() {
    if ($errors) display_errors;
    global $global;
    global $conf;
    $db = $global['db'];
?>
    <h2><?php echo _('Confirm Registration Details of ') . $_SESSION['camp_name'] ?></h2>
    <?php
    shn_form_fopen("ecmp", null, array('req_message' => false, 'name' => ""));
    shn_form_fsopen(_('General Details'));
    shn_form_label(_("Shelter Name") . " : ", $_SESSION['camp_name']);
    $q = "select option_description from field_options where field_name='opt_camp_type' and option_code='" . $_SESSION['opt_camp_type'] . "'";
    $ref = $db->Execute($q);
    shn_form_label(_("Shelter Type") . " : ", $ref->fields[0]);
    shn_form_label(_("Address") . " : ", $_SESSION['camp_address']);
    shn_form_fsclose();
    shn_form_fsopen(_('Location Details'));
    $location = _shn_cr_location_string($_SESSION['cr']['loc']);
    shn_form_label(_("Location") . " : ", $location);
    shn_form_fsclose();
    shn_form_fsopen(_("Map Location"));
    shn_form_label(_("Latitude : "), $_SESSION['camp_lat']);
    shn_form_label(_("Longitude : "), $_SESSION['camp_lon']);
    shn_form_fsclose();
    shn_form_fsopen(_('Contact Person Details'));
    shn_form_label(_("Full Name") . " : ", $_SESSION['camp_contact_name']);
    shn_form_label(_("Phone Number") . " : ", $_SESSION['camp_contact_number']);
    shn_form_label(_("Mobile Number") . " : ", $_SESSION['camp_contact_mob']);
    shn_form_label(_("Occupation") . " : ", $_SESSION['camp_occupation']);
    shn_form_fsclose();
    shn_form_fsopen(_('Shelter Population'));
    shn_form_label(_("Capacity") . " : ", $_SESSION['camp_capacity']);
    shn_form_label(_("Men") . " : ", $_SESSION['camp_men']);
    shn_form_label(_("Women") . " : ", $_SESSION['camp_women']);
    shn_form_label(_("Children( 1 ~ 12 years old )") . " : ", $_SESSION['camp_children']);
    shn_form_label(_("Total Count") . " : ", $_SESSION['camp_total']);
    echo '<hr />';
    shn_form_label(_("Infected Count") . " : ", $_SESSION['camp_family']);
    shn_form_label(_('Update time') . " : ", $_SESSION['camp_modified']);
    shn_form_hidden(array('seq' => 'commit'));
    shn_form_fsclose();
    /*shn_form_fsopen(_('GPS Coordinates'));
    shn_form_label(_("Latitude : "),$_SESSION['gis_loc_y']);
    shn_form_label(_("Longitude : "),$_SESSION['gis_loc_x']);
    
    shn_form_fsclose();*/
    shn_form_fsopen(_('Services / Facilities Available'));
    if (!isset($_SESSION['hospital'])) {
        $_SESSION['opt_camp_service'] = $_POST['opt_camp_service'];
        $_SESSION['camp_comments'] = $_POST['comments'];
    }
    $a = "select option_code,option_description from field_options where field_name='opt_camp_service'";
    $ref = $db->Execute($a);
    while (!$ref->EOF) {
        $val = $ref->fields[0];
        $name = $ref->fields[1];
        $flag = false;
        if (isset($_SESSION['opt_camp_service'])) {
            foreach($_SESSION['opt_camp_service'] as $a => $b) {
                if ($val == $b) {
                    shn_form_label(_lc($name) . " : ", _('Available'));
                    $flag = true;
                }
            }
        }
        if (!$flag) {
            shn_form_label(_lc($name) . " : ", _('Not Available'));
        }
?>
		<?php
        $ref->MoveNext();
    }
    shn_form_fsclose();
    echo '<center>';
    shn_form_submit(_("Finish"), 'name="finish"');
    shn_form_submit(_("Edit"), 'name="edit"');
    echo '</center>';
    shn_form_fclose();
}
function _shn_cr_cedit_second() {
    shn_form_fopen(ecmp);
    shn_form_fsopen(_("General Details"));
    shn_form_hidden(array('seq' => 'chk'));
    shn_form_hidden(array('cmp_id' => $_SESSION['editid']));
    shn_form_text(_("Shelter Name"), "camp_name", 'size="50"', array('req' => true, 'value' => $_SESSION['camp_name']));
    shn_form_opt_select("opt_camp_type", _("Shelter Type"), null, array('value' => $_SESSION['opt_camp_type']));
    shn_form_textarea(_("Address"), "camp_address", null, array('value' => $_SESSION['camp_address']));
    shn_form_fsclose();
?>

	<?php
    global $global, $range, $conf;
    include_once $global['approot'] . "/inc/lib_location.inc";
    shn_form_fsopen(_("Location Details"));
    shn_location($range, $_SESSION['cr']['loc']);
    shn_form_fsclose();
    shn_form_fsopen(_("Map Location"));
    echo '<div class=\'message information\'>';
    echo _('Click on the button "Update the location" will update the map location if you did manually modify the values of position.');
    echo "</div>";
    $extra_opts['req'] = false;
    $extra_opts['value'] = $_SESSION['camp_lat'];
    shn_form_text(_("Latitude : "), 'gps_x', 'size="40"', $extra_opts);
    $extra_opts['value'] = $_SESSION['camp_lon'];
    shn_form_text(_("Longitude : "), 'gps_y', 'size="40"', $extra_opts);
    shn_form_button(_('Update the location'));
    shn_form_fsclose();
    if ($conf['gis']) {
        $extra_opts['marker'] = 'single';
        shn_form_fsopen($name_of_map);
        $plugin_name = $conf['mod_gis_dflt'];
        include $global['approot'] . "/mod/gis/plugins/" . "$plugin_name" . "/handler_" . "$plugin_name" . ".inc";
        echo "<div class='message information'>";
        echo _("You can move around and enlarge/reduce the size of the area you want using
the scale on upper left corner of the map. By clicking on a map you can
mark your location with a pointer.");
        echo "</div>";
        show_add_marker_map($nameOfPoint, $extra_opts);
        shn_form_fsclose();
    }
    //-----------------------------------------
    shn_form_fsopen(_("Contact Person Details"));
    shn_form_text(_("Full Name"), "camp_contact_name", 'size="60"', array('value' => $_SESSION['camp_contact_name']));
    shn_form_text(_("Phone Number"), "camp_contact_number", 'size="60"', array('value' => $_SESSION['camp_contact_number']));
    shn_form_text(_("Mobile Number"), "contact_mob", 'size="60"', array('value' => $_SESSION['camp_contact_mob']));
    shn_form_text(_("Occupation"), "occupation", 'size="60"', array('value' => $_SESSION['camp_occupation']));
    shn_form_fsclose();
    shn_form_fsopen(_("Shelter Population"));
    shn_form_text(_("Capacity"), "capacity", 'size="10"', array('value' => $_SESSION['camp_capacity']));
    shn_form_text(_("Men"), "men", 'size="10"', array('value' => $_SESSION['camp_men']));
    shn_form_text(_("Women"), "women", 'size="10"', array('value' => $_SESSION['camp_women']));
    shn_form_text(_("Children( 1 ~ 12 years old )"), "children", 'size="10"', array('value' => $_SESSION['camp_children']));
    echo '<hr />';
    shn_form_text(_("Infected Count"), "family", 'size="10"', array('value' => $_SESSION['camp_family']));
    shn_form_date(_('Update time'), 'modified', array(
        'value' => $_SESSION['camp_modified']
    ));
    shn_form_fsclose();
    shn_form_submit(_("Next"));
    shn_form_fclose();
}