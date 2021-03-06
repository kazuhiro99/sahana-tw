<?php
/*{{{ Level1 Form */
/**
 * _shn_ims_level1_form
 *
 * @param mixed $errors
 * @param mixed $updated
 * @access protected
 * @return void
 */
function _shn_ims_level1_form($errors = false, $type = null) {
    global $global;
    global $conf;
    if ($errors) display_errors();
    $sql = "SELECT incident_id, name FROM incident WHERE parent_id IS NULL";
    $arr = $global['db']->GetAll($sql);
    if (!empty($arr)) {
        shn_form_fopen("ims_level1", null);
        if ($type == 'Updated' || $type == 'Deleted') {
            shn_form_fsopen("");
?>			<p align="center"><?=$type; ?></p>
<?php
            shn_form_fsclose();
        }
        shn_form_hidden(array('seq' => 'update'));
        shn_form_fsopen(_('Manage ') . _lc($conf['mod_admin_ims_level1']));
?>
		<table>
		<thead>
    	<td width="100%"><strong><?php echo _('Name'); ?></strong></td>
    	<td width="100%"><strong><?php echo _('Delete'); ?></strong></td>
		</thead>
<?php
        foreach($arr as $row) {
?>
			<tr>
    		<td>
    		<?php shn_form_text('', 'level1_name[' . $row['incident_id'] . ']', null, array('value' => $row['name'], 'no_label' => true, 'req' => true)); ?>
    		</td>
    		<td><input type="checkbox" name="level1_delete[<?=$row['incident_id']; ?>]" />
    		</td>
			</tr>
<?php
        }
?>
		</table>
<?php
        shn_form_fsclose();
        shn_form_submit(_('Update'));
        shn_form_fclose();
    }
    shn_form_fopen("ims_level1", null, array('req_message' => false));
    if ($type == 'added') {
        shn_form_fsopen("");
?>		<p align="center"><?=$type; ?></p>
<?php
        shn_form_fsclose();
    }
    shn_form_hidden(array('seq' => 'addnew'));
    shn_form_fsopen(_('Add New ') . _lc($conf['mod_admin_ims_level1']));
    shn_form_text(_("Name"), 'level1_name_new', null, array('req' => true));
    shn_form_fsclose();
    shn_form_submit(_('Add New'));
    shn_form_fclose();
}
/* }}} */
/* {{{ Level1 Validation */
/**
 * _shn_ims_config_validate
 *
 * @access protected
 * @return void
 */
function _shn_ims_level1_validate() {
    global $conf;
    global $global;
    $error_flag = false;
    //clean the post
    shn_tools_clean_post(&$local_post);
    //anything entered?
    if (empty($local_post)) {
        add_error(_("You have not completed the form"));
        return false;
    }
    if (($local_post['seq']) == 'addnew') {
        $sql = "SELECT name FROM incident WHERE name = '{$local_post['level1_name_new']}'";
        $incident_name = $global['db']->GetOne($sql);
        if (!isset($local_post['level1_name_new'])) {
            add_error(sprintf(_("Please enter the name for %s"), strtolower($conf['mod_admin_ims_level1'])));
            add_warning(sprintf(_('If there is/are no %1$s(s), please add a new %2$s'), strtolower($conf['mod_admin_ims_level1']), strtolower($conf['mod_admin_ims_level1'])));
            $error_flag = true;
        }
        else if(shn_check_for_special_char($local_post['level1_name_new'])) {
            $error_flag=true;
        }
        else if(strtolower($incident_name) == strtolower(trim($local_post['level1_name_new']))) {
            add_warning(sprintf(_("$incident_name is already exists.")));
            $error_flag=true;
        }
    } else {
        $local_post['level1_name'] = null;
        foreach($_POST['level1_name'] as $k => $v) {
            $v = trim($v);
            $k = trim($k);
            if ($v != '') $local_post['level1_name'][$k] = $v;
        }
        if (isset($_POST['level1_delete'])) {
            $local_post['level1_delete'] = null;
            foreach($_POST['level1_delete'] as $k => $v) {
                $v = trim($v);
                $k = trim($k);
                if ($v != '') $local_post['level1_delete'][$k] = $v;
            }
        }
    }
    if ($error_flag) return false;
    else {
        if (($local_post['seq']) == 'addnew') {
            $sql = "INSERT INTO incident (name) VALUES ('{$local_post['level1_name_new']}')";
            $global['db']->Execute($sql);
        } else {
            //Update
            foreach($local_post['level1_name'] as $k => $v) {
                $sql = "UPDATE incident SET name='$v' WHERE incident_id='$k'";
                $global['db']->Execute($sql);
            }
            //Delete
            if (isset($_POST['level1_delete'])) {
                foreach($local_post['level1_delete'] as $k => $v) {
                    $sql = "DELETE FROM incident WHERE incident_id='$k'";
                    $global['db']->Execute($sql);
                }
            }
        }
        include_once $global['approot']."/inc/lib_misc.inc";
        shn_page_reload('admin', 'ims_level1');
    }
}
/* }}} */
/*{{{ Level2 Form */
/**
 * _shn_ims_level2_form
 *
 * @param mixed $errors
 * @param mixed $updated
 * @access protected
 * @return void
 */
function _shn_ims_level2_form($errors = false, $type = null) {
    global $global;
    global $conf;
    if ($errors) display_errors();
    $sql = "SELECT incident_id, name FROM incident WHERE parent_id IS NULL";
    $arr = $global['db']->GetAll($sql);
    foreach($arr as $row) {
        $parent_ids[$row['incident_id']] = $row['name'];
    }
    $sql = "SELECT  a.incident_id as parent_id, b.name, b.incident_id FROM incident a INNER JOIN incident b ON a.incident_id = b.parent_id AND a.parent_id IS NULL";
    $arr = $global['db']->GetAll($sql);
    if (!empty($arr)) {
        shn_form_fopen("ims_level2", null);
        if ($type == 'Updated' || $type == 'Deleted') {
            shn_form_fsopen("");
?>			<p align="center"><?=$type; ?></p>
<?php
            shn_form_fsclose();
        }
        shn_form_hidden(array('seq' => 'update'));
        shn_form_fsopen(_('Manage ') . _($conf['mod_admin_ims_level2']));
?>
		<table width="100%">
		<thead>
   		<td><strong><?php echo _('Name'); ?></strong></td>
   		<td><strong><?php echo _lc($conf['mod_admin_ims_level1']); ?></strong></td>
    	<td><strong><?php echo _('Delete'); ?></strong></td>
		</thead>
<?php
        foreach($arr as $row) {
?>
			<tr>
    		<td>
    		<?php shn_form_text('', 'level2_name[' . $row['incident_id'] . ']', null, array('value' => $row['name'], 'no_label' => true, 'req' => true)); ?>
    		</td>
    		<td>
    		<select name="level2_parent_id[<?=$row['incident_id']; ?>]">
<?php
            foreach($parent_ids as $parent_id => $name) {
?>
        		<option value="<?=$parent_id; ?>" <?=($parent_id == $row['parent_id'] ? 'selected' : ''); ?> >
            	<?=$name; ?>
        		</option>
<?php
            }
?>
    	</select>
    	</td>
    	<td><input type="checkbox" name="level2_delete[<?=$row['incident_id']; ?>]" />
    	</td>
		</tr>
<?php
        }
?>
		</table>
<?php
        shn_form_fsclose();
        shn_form_submit(_('Update'));
        shn_form_fclose();
    }
    shn_form_fopen("ims_level2", null, array('req_message' => false));
    if ($type == 'added') {
        shn_form_fsopen("");
?>		<p align="center"><?=$type; ?></p>
<?php
        shn_form_fsclose();
    }
    shn_form_hidden(array('seq' => 'addnew'));
    shn_form_fsopen(_('Add New ') . _lc($conf['mod_admin_ims_level2']));
    shn_form_select($parent_ids, _lc($conf['mod_admin_ims_level1']), "level2_new_parent_id");
    shn_form_text(_("Name"), 'level2_name_new', null, array('req' => true));
    shn_form_fsclose();
    shn_form_submit(_('Add New'));
    shn_form_fclose();
}
/* }}} */
/* {{{ Level2 Validation */
/**
 * _shn_ims_config_validate
 *
 * @access protected
 * @return void
 */
function _shn_ims_level2_validate() {
    global $conf;
    global $global;
    $error_flag = false;
    //clean the post
    shn_tools_clean_post(&$local_post);

    $sql = "SELECT  b.name FROM incident a
    INNER JOIN incident b ON a.incident_id = b.parent_id AND a.parent_id IS NULL
    WHERE b.name = '{$local_post['level2_name_new']}' AND b.parent_id = '{$local_post['level2_new_parent_id']}'";

    $incident_event_name = $global['db']->GetOne($sql);
    
    //anything entered?
    if (empty($local_post)) {
        add_error(_("You have not completed the form"));
        return false;
    }
    if (($local_post['seq']) == 'addnew') {
        if (!isset($local_post['level2_name_new'])) {
            add_error(sprintf(_("Please enter a name for the %s"), strtolower($conf['mod_admin_ims_level2'])));
            $error_flag = true;
        }
        if (!isset($local_post['level2_new_parent_id'])) {
            add_error(sprintf(_("Please select a %s"), strtolower($conf['mod_admin_ims_level1'])));
            $error_flag = true;
        }
        if(shn_check_for_special_char($local_post['level2_name_new'])) {
            $error_flag = true;
        }
        if($incident_event_name == $local_post['level2_name_new']) {
            add_warning($local_post['level2_name_new'] . _(" is already exists."));
            $error_flag = true;
        }
    } else {
        $local_post['level2_name'] = null;
        foreach($_POST['level2_name'] as $k => $v) {
            $v = trim($v);
            $k = trim($k);
            if ($v != '') $local_post['level2_name'][$k] = $v;
        }
        $local_post['level2_parent_id'] = null;
        foreach($_POST['level2_parent_id'] as $k => $v) {
            $v = trim($v);
            $k = trim($k);
            if ($v != '') $local_post['level2_parent_id'][$k] = $v;
        }
        if (isset($_POST['level2_delete'])) {
            $local_post['level2_delete'] = null;
            foreach($_POST['level2_delete'] as $k => $v) {
                $v = trim($v);
                $k = trim($k);
                if ($v != '') $local_post['level2_delete'][$k] = $v;
            }
        }
    }
    if ($error_flag) return false;
    else {
        if (($local_post['seq']) == 'addnew') {
            $sql = "INSERT INTO incident (name,parent_id) VALUES ('{$local_post['level2_name_new']}','{$local_post['level2_new_parent_id']}')";
            $global['db']->Execute($sql);
        } else {
            //Update
            foreach($local_post['level2_name'] as $k => $v) {
                $sql = "UPDATE incident SET name='$v' WHERE incident_id='$k'";
                $global['db']->Execute($sql);
                #    echo $sql."<br >";
                
            }
            foreach($local_post['level2_parent_id'] as $k => $v) {
                $sql = "UPDATE incident SET parent_id='$v' WHERE incident_id='$k'";
                $global['db']->Execute($sql);
                #    echo $sql."<br >";
                
            }
            //Delete
            if (isset($_POST['level2_delete'])) {
                foreach($local_post['level2_delete'] as $k => $v) {
                    $sql = "DELETE FROM incident WHERE incident_id='$k'";
                    $global['db']->Execute($sql);
                    #        echo $sql."<br >";
                    
                }
            }
        }
        include_once $global['approot']."/inc/lib_misc.inc";
        shn_page_reload('admin', 'ims_level2');
    }
}
/* }}} */
/*{{{ Level3 Form */
/**
 * _shn_ims_level3_form
 *
 * @param mixed $errors
 * @param mixed $updated
 * @access protected
 * @return void
 */
function _shn_ims_level3_form($errors = false, $type = null) {
    global $global;
    global $conf;
    if ($errors) display_errors();
    $sql = "SELECT a.incident_id, a.name FROM incident a INNER JOIN incident b ON a.parent_id = b.incident_id and b.parent_id IS NULL";
    $arr = $global['db']->GetAll($sql);
    $parent_ids = array();
    foreach($arr as $row) {
        $parent_ids[$row['incident_id']] = $row['name'];
    }
    $sql = "SELECT a.incident_id, a.name, b.incident_id as parent_id FROM incident a INNER JOIN incident b  ON a.parent_id = b.incident_id INNER JOIN incident c ON b.parent_id = c.incident_id AND c.parent_id IS NULL";
    $arr = $global['db']->GetAll($sql);
    if (!empty($arr)) {
        shn_form_fopen("ims_level3", null);
        if ($type == 'Updated' || $type == 'Deleted') {
            shn_form_fsopen("");
?>			<p align="center"><?=$type; ?></p>
<?php
            shn_form_fsclose();
        }
        shn_form_hidden(array('seq' => 'update'));
        shn_form_fsopen(_('Manage ') . _($conf['mod_admin_ims_level3']));
?>
		<table width="100%">
		<thead>
    	<td><strong><?php echo _('Name'); ?></strong></td>
    	<td><strong><?php echo _($conf['mod_admin_ims_level2']); ?></strong></td>
    	<td><strong><?php echo _('Delete'); ?></strong></td>
		</thead>
<?php
        foreach($arr as $row) {
?>
			<tr>
    		<td>
    		<?php
            shn_form_text('', 'level3_name[' . $row['incident_id'] . ']', null, array('value' => $row['name'], 'req' => true, 'no_label' => true));
?>
    		</td>
    		<td>
    		<select name="level3_parent_id[<?=$row['incident_id']; ?>]">
<?php
            foreach($parent_ids as $parent_id => $name) {
?>
        		<option value="<?=$parent_id; ?>" <?=($parent_id == $row['parent_id'] ? 'selected' : ''); ?> >
            	<?=$name; ?>
        		</option>
<?php
            }
?>
    		</select>
    		</td>
   			<td><input type="checkbox" name="level3_delete[<?=$row['incident_id']; ?>]" />
   			</td>
			</tr>
<?php
        }
?>
		</table>
<?php
        shn_form_fsclose();
        shn_form_submit(_('Update'));
        shn_form_fclose();
    }
    shn_form_fopen("ims_level3", null, array('req_message' => false));
    if ($type == 'added') {
        shn_form_fsopen("");
?>		<p align="center"><?=$type; ?></p>
<?php
        shn_form_fsclose();
    }
    shn_form_hidden(array('seq' => 'addnew'));
    shn_form_fsopen(_('Add New ') . _($conf['mod_admin_ims_level3']));
    shn_form_select($parent_ids, _($conf['mod_admin_ims_level2']), "level3_new_parent_id");
    shn_form_text(_("Name"), 'level3_name_new', null, array('req' => true));
    shn_form_fsclose();
    shn_form_submit(_('Add New'));
    shn_form_fclose();
}
/* }}} */
/* {{{ Level3 Validation */
/**
 * _shn_ims_config_validate
 *
 * @access protected
 * @return void
 */
function _shn_ims_level3_validate() {
    global $conf;
    global $global;
    $error_flag = false;
    //clean the post
    shn_tools_clean_post(&$local_post);
    //anything entered?
    if (empty($local_post)) {
        add_error(_("You have not completed the form"));
        return false;
    }
    if (($local_post['seq']) == 'addnew') {
        if (!isset($local_post['level3_name_new'])) {
            add_error(sprintf(_("Please enter a name for the %s"), strtolower($conf['mod_admin_ims_level3'])));
            $error_flag = true;
        }
        if (!isset($local_post['level3_new_parent_id'])) {
            add_error(sprintf(_('Please select a %s.'), $conf['mod_admin_ims_level2']));
            add_warning(_('If there is/are no %1$s(s), please add a new %2$s'), strtolower($conf['mod_admin_ims_level2']), strtolower($conf['mod_admin_ims_level2']));
            $error_flag = true;
        }

        if(shn_check_for_special_char($local_post['level3_name_new'])) {
            $error_flag = true;
        }
    } else {
        $local_post['level3_name'] = null;
        foreach($_POST['level3_name'] as $k => $v) {
            $v = trim($v);
            $k = trim($k);
            if ($v != '') $local_post['level3_name'][$k] = $v;
        }
        $local_post['level3_parent_id'] = null;
        foreach($_POST['level3_parent_id'] as $k => $v) {
            $v = trim($v);
            $k = trim($k);
            if ($v != '') $local_post['level3_parent_id'][$k] = $v;
        }
        if (isset($_POST['level3_delete'])) {
            $local_post['level3_delete'] = null;
            foreach($_POST['level3_delete'] as $k => $v) {
                $v = trim($v);
                $k = trim($k);
                if ($v != '') $local_post['level3_delete'][$k] = $v;
            }
        }
    }
    if ($error_flag) return false;
    else {
        if (($local_post['seq']) == 'addnew') {

            $sql = "SELECT * FROM incident WHERE name='{$local_post['level3_name_new']}' AND parent_id='{$local_post['level3_new_parent_id']}'";
            $res=$global['db']->Execute($sql);
            $parent_idset = '';
            foreach($res as $key => $val) {
                $parent_idset.=$val['parent_id'];
            }
            $sql = "INSERT INTO incident (name,parent_id) VALUES ('{$local_post['level3_name_new']}','{$local_post['level3_new_parent_id']}')";
            $global['db']->Execute($sql);
        } else {
            //Update
            foreach($local_post['level3_name'] as $k => $v) {
                $sql = "UPDATE incident SET name='$v' WHERE incident_id='$k'";
                $global['db']->Execute($sql);
                #    echo $sql."<br >";
                
            }
            foreach($local_post['level3_parent_id'] as $k => $v) {
                $sql = "UPDATE incident SET parent_id='$v' WHERE incident_id='$k'";
                $global['db']->Execute($sql);
                #    echo $sql."<br >";
                
            }
            //Delete
            if (isset($_POST['level3_delete'])) {
                foreach($local_post['level3_delete'] as $k => $v) {
                    $sql = "DELETE FROM incident WHERE incident_id='$k'";
                    $global['db']->Execute($sql);
                    #        echo $sql."<br >";
                    
                }
            }
        }

        if($parent_idset != null) {
            $message=$local_post['level3_name_new']._(" Already exists under ").$conf['mod_admin_ims_level3'];
            add_warning($message);
        }

        include_once $global['approot']."/inc/lib_misc.inc";
        shn_page_reload('admin', 'ims_level3');
    }
}
/* }}} */
?>
