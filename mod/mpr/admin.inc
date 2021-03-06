<?php
/* $Id: admin.inc,v 1.10.18.5 2008/04/08 03:59:10 ravithb Exp $ */
/**
 * Administration of the Missing Person Registry
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');

/* {{{ Sub Menus */
/**
 * shn_mpr_adminmenu
 *
 * @access public
 * @return void
 */
function shn_mpr_adminmenu() {
    global $global;
    $module = $global['module'];
    // Create the module menu
    shn_adm_menuopen(_("Missing Person Registry"));
    shn_adm_menuitem("adm_gen", _("General Configuration"));
    //	shn_adm_menuitem("adm_images", _("Manage Images"));
    shn_adm_menuitem("adm_opt_age_group", _("Manage Age Groups"));
    shn_adm_menuitem("adm_opt_race", _("Manage Race"));
    shn_adm_menuitem("adm_opt_religion", _("Manage Religion"));
    shn_adm_menuitem("adm_opt_blood_type", _("Manage Blood Group"));
    shn_adm_menuitem("adm_opt_eye_color", _("Manage Eye Colors"));
    shn_adm_menuitem("adm_opt_hair_color", _("Manage Hair Colors"));
    shn_adm_menuitem("adm_opt_skin_color", _("Manage Skin Colors"));
    shn_adm_menuclose();
}

/* }}} */
/* {{{ Default */
/**
 * shn_mpr_adm_default
 *
 * @access public
 * @return void
 */
function shn_mpr_adm_default() {
    shn_mpr_adminmenu();
    ?> <br />
<p><b><?php echo _("Welcome to the Missing Person Registry admin page"); ?> </b></p>
<p><?php echo _("Please use the navigation menu above to configure each field."); ?> </p>
    <?php
//shn_mpr_adm_gen();
}

/* }}} */
//temporary fix
function _shn_mpr_adm_gen_validate() {
    clean_errors();
    $error_flag = false;
    $limit = $_POST['search_limit'];
    if ($limit == '' | $limit == null) {
        add_error(_("Please enter the no of images per page."));
        $error_flag = true;
    } else if (!shn_valid_number($limit)) {
        $error_flag = true;
        add_error(_("Search limit should be a number"));
    }
    return $error_flag;
}

//added by isuru
function shn_mpr_insert_to_config($val) {
    global $global;
    $db = $global["db"];
    $q1 = "delete from config where confkey='mod_mpr_pictures_per_page'";
    $db->Execute($q1);
    $q2 = "insert into config values('','mpr','mod_mpr_pictures_per_page','{$val}')";
    $db->Execute($q2);
}

/* {{{ shn_mpr_adm_gen */
function shn_mpr_adm_gen() {
    shn_mpr_adminmenu();
    if (isset($_POST['seq']) && $_POST['seq'] == 'general') {
        if (_shn_mpr_adm_gen_validate()) {
            _shn_mpr_adm_gen(true, false);
        } else {
            shn_mpr_insert_to_config($_POST['search_limit']);
            _shn_mpr_adm_gen(false, true);
        }
    } else {
        _shn_mpr_adm_gen();
    }
}

/* }}} */
/* {{{ shn_mpr_adm_images */
function shn_mpr_adm_images() {
    shn_mpr_adminmenu();
    ?><br /><h2><?php echo _("Manage Search"); ?></h2>
    <?php
}

/* }}} */
/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_age_group() {
    shn_mpr_adminmenu();
    //print 'button is'.$_POST['button_name'];

    ?><br /><h2><?php echo _("Manage Age Groups"); ?></h2>
    <?php
    _shn_mpr_adm_field_options_controller('opt_age_group');
}

/* }}} */
/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_race() {
    shn_mpr_adminmenu();
    ?><br /><h2><?php echo _("Manage Race"); ?></h2>
    <?php
    _shn_mpr_adm_field_options_controller('opt_race');
}

/* }}} */
/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_religion() {
    shn_mpr_adminmenu();
    ?><br /><h2><?php echo _("Manage Religion"); ?></h2>
    <?php
    _shn_mpr_adm_field_options_controller('opt_religion');
}

/* }}} */
/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_blood_type() {
    shn_mpr_adminmenu();
    ?><br /><h2><?php echo _("Manage Blood Groups"); ?></h2>
    <?php
    _shn_mpr_adm_field_options_controller('opt_blood_type');
}

/* }}} */
/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_eye_color() {
    shn_mpr_adminmenu();
    ?><br /><h2><?php echo _("Manage Eye Color"); ?></h2>
    <?php
    _shn_mpr_adm_field_options_controller('opt_eye_color');
}

/* }}} */
/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_hair_color() {
    shn_mpr_adminmenu();
    ?><br /><h2><?php echo _("Manage Hair Color"); ?></h2>
    <?php
    _shn_mpr_adm_field_options_controller('opt_hair_color');
}

/* }}} */
/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_skin_color() {
    shn_mpr_adminmenu();
    ?><br /><h2><?php echo _("Manage Skin Color"); ?></h2>
        <?php
        _shn_mpr_adm_field_options_controller('opt_skin_color');
    }

    /* }}} */
    /* {{{ */
    function _shn_mpr_adm_gen($errors = false, $updated = false) {
        global $conf;
        if ($errors) display_errors();
        if ($updated) {
            ?>
<p align="center">

            <?php add_confirmation(_("Updated"));
        }
        ?><br /><h2><?php echo _("General Configuration"); ?></h2><?php
        shn_form_fopen("adm_gen", null);
        shn_form_hidden(array('seq' => 'general'));
        //shn_form_fsopen(_('Name'));
        if (!isset($_POST['name'])) $val = array('value' => $conf['mod_mpr_name']);
        else $val = null;
        //shn_form_text(_('Module Name'), 'name', 'size="20"', $val);
        //shn_form_fsclose();
        shn_form_fsopen(_('Search'));
        if (!isset($_POST['search_limit'])) $val = array('value' => $conf['mod_mpr_pictures_per_page']);
        else $val = null;
        $val['req'] = true;
        shn_form_text(_('Number of images per page'), 'search_limit', 'size="15"', $val);
        shn_form_fsclose();
        #    shn_form_fsopen(_('Upload Pictures'));
        #    shn_form_select(array('database'=>_('To Database'),
        #                        'file'=>_('To File')), _('Image save handler'), 'upload_pic_handler');
        #    shn_form_fsclose();
        shn_form_submit(_('Update'));
        shn_form_fclose();
    }

    /* }}} */
    /* {{{ ACL Install */
    /**
     * shn_mpr_adm_acl_install
     *
     * @access public
     * @return void
     */
    function shn_mpr_adm_acl_install() {
        global $global;
        $db = $global["db"];
        $q = "select value from config where module_id='mpr' and confkey='acl_base'";
        $res_acl = $db->Execute($q);
        if (!$res_acl->EOF && $res_acl->fields[0] == 'installed') {
            $msg = _("ACL Base for Missing Person Registry is already installed, This is a reinstall");
        }
        include_once $global['approot'] . 'inc/lib_security/acl_api.inc';
        include_once $global['approot'] . 'inc/lib_security/acl.inc';
        include_once $global['approot'] . 'inc/lib_security/authenticate.inc';
        $acl = new SahanaACL(NULL);
        /* start of or specifc ACL entries
        */
        $res = shn_acl_add_module("mpr", _("Missing Person Registry"));
        $res = shn_acl_add_action_group("mpr", "deny_admin", _("Deny admin group"));
    $res = shn_acl_add_action("mpr", "deny_admin", "shn_mpr_adm_default", _("Display Admin page"));
        ## Deny permission for 'deny_admin' action group with in 'or' to 'guest' role
    $res = shn_acl_add_perms_action_group_role('guest', 'mpr', 'deny_admin');
    $res = shn_acl_add_perms_action_group_role('user', 'mpr', 'deny_admin');
    $res = shn_acl_add_action_group("mpr", "deny_user", "Deny user group");
    $res = shn_acl_add_action("mpr", "deny_user", "shn_mpr_addmp", _("Add Person"));
    $res = shn_acl_add_action("mpr", "deny_user", "shn_mpr_editmp", _("Edit Person"));
    $res = shn_acl_add_action("mpr", "deny_user", "shn_mpr_add_tracker", _("Add Tracker"));
    $res = shn_acl_add_perms_action_group_role('guest', 'mpr', 'deny_user');
    if ($res_acl->EOF) $q = "insert into config values('mpr','acl_base','installed')";
    else $q = "update config set value='installed' where module_id='mpr' and confkey='acl_base'";
    $res = $db->Execute($q);
    $msg = _("ACL Base for Missing Person Registry was successfully installed");
    ?>
<div id="result_msg">
    <?php echo $msg; ?>
</div>
<br />
    <?php
}

/* }}} */
//temporary fix
function _shn_mpr_adm_field_options_controller($type) {
    $seq = isset($_POST['seq']) ? $_POST['seq'] : '';
    switch ($seq) {
        case 'update':
            if (_shn_mpr_adm_field_options_validate($type)) {
                _shn_mpr_adm_field_options_form($type, false);
            } else {
                _shn_mpr_adm_field_options_form($type, true);
            }
            break;
        default:
            _shn_mpr_adm_field_options_form($type);
            break;
    }
}

function _shn_mpr_delete_option($optioncode) {
    global $global;
    $sql = "DELETE FROM field_options WHERE option_code='{$optioncode}'";
    $global['db']->Execute($sql);
    add_confirmation(_('Field was successfully deleted.'));
}

function is_optioncode_exists($optioncode) {
    $found = false;
    global $global;
    $sql = "SELECT * FROM field_options WHERE option_code='{$optioncode}'";
    $res = $global['db']->Execute($sql);
    while (!$res->EOF) {
        $code = $res->fields['option_code'];
        $found = true;
        $res->MoveNext();
    }
    return $found;
}

function _shn_mpr_update_option($optioncode, $optiondescription) {
    global $global;
    $sql = "UPDATE field_options SET option_description='{$optiondescription}' WHERE option_code='{$optioncode}'";
    $global['db']->Execute($sql);
//add_confirmation($optiondescription.' updated');
}

function _shn_mpr_insert_option($field_name, $optioncode, $optiondescription) {
    global $global;
    $sql = "INSERT INTO field_options (field_name,option_code,option_description) VALUES ('{$field_name}','{$optioncode}','{$optiondescription}')";
    $global['db']->Execute($sql);
    if ($sql) {
        add_confirmation(_($_POST['new_desc'] . ' was successfully added.'));
    }
    $_POST['new_code'] = $_POST['new_desc'] = null;
}

function _shn_mpr_adm_field_options_form($type) {
    global $global;
    global $conf;
    $button_type = isset($_POST['button_name']) ? $_POST['button_name'] : '';
    if ($button_type == _('Update')) {
        $sql = "SELECT field_name, option_code, option_description  FROM field_options WHERE field_name = '{$type}'";
        $sel = $global['db']->GetAll($sql);
        $count = 0;
        foreach ($sel as $row) {
            $opcode = $row['option_code'];
            $fname = $row['field_name'];
            $code = $_POST[$opcode];
            $desc = isset($_POST[$count]) ? $_POST[$count] : '';
            ++$count;
            $todelete = isset($_POST[$count]) ? $_POST[$count] : '';
            ++$count;
            if ($todelete == 'on') {
                _shn_mpr_delete_option($code);
            } else {
                _shn_mpr_update_option($code, $desc);
            }
        }
    } else if ($button_type == _('AddNew')) {
        if (empty($_POST['new_code'])) {
            add_error(_("Please enter the code"));
            display_errors();
        } else if(empty($_POST['new_desc'])) {
            add_error(_("Please  enter the description"));
            display_errors();
        } else if (is_optioncode_exists($_POST['new_code'])) {
            add_error(_("Code already exists"));
            display_errors();
        } else _shn_mpr_insert_option($type, $_POST['new_code'], $_POST['new_desc']);
    }
    $sql = "SELECT field_name, option_code, option_description  FROM field_options WHERE field_name = '{$type}'";
    $arr = $global['db']->GetAll($sql);
    if (!empty($arr)) {
        shn_form_fopen('adm_' . $type, null);
        shn_form_fsopen(_('Update'));
        shn_form_hidden(array('seq' => 'update'));
        ?>
<table>
    <thead>
        <td><strong><?php echo _('Code'); ?></strong></td>
        <td width="100%"><strong><?php echo _('Description'); ?></strong></td>
        <td width="100%"><strong><?php echo _('Delete'); ?></strong></td>
    </thead>
    <tbody>
        <?php
        $count = 0;
        foreach ($arr as $row) {
            ?>
        <tr>
            <td><input type="text" READONLY name="<?=$row['option_code']; ?>"
                       value="<?=$row['option_code']; ?>"  />
            </td>
            <td><input type="text" name="<?=$count++;?>"
                       value="<?=$row['option_description']; ?>" />
            </td>
            <td><input type="checkbox" name="<?=$count++;?>" />
            </td>
        </tr>
            <?php
        }
        ?>
    </tbody>
</table>
        <?php
        shn_form_submit(_('Update'), "name='button_name'");
        shn_form_fsclose();
    }
    shn_form_fsopen(_('Add New '));
    shn_form_text(_("Code"), 'new_code', null, array('req' => true));
    shn_form_text(_("Description"), 'new_desc', null, array('req' => true));
    shn_form_submit(_('AddNew'), "name='button_name'");
    shn_form_fclose();
}

function _shn_mpr_adm_field_options_validate($type, $error = false) {

}