<?php
/* $Id: home.inc,v 1.5.24.4 2009/01/06 22:06:53 franboon Exp $ */
/** 
 * Home Page of the Missing Person Registry
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @author	   J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
?>
<div id="home">
<h2><?php echo _('Synchronization Module'); ?></h2>
<!-- <img src="theme/default/img/mpr.png"/> -->
<p><?php echo _('This module helps you to synchronize two separate Sahana installations and share information among the independent Sahana instances.'); ?><br /><br />


    <div><h3><b><em><?=(_("Features Include:")) ?></em></b></h3></div>
<br><br />

</p>
<ul>
    <li><?php echo _('Import and export information among Sahana instances'); ?></li>
    <li><?php echo _('Allows details of the data sharing history among selected Sahana installations'); ?></li>
</ul>


<strong><?php echo _('Description of Actions:') ?></strong><br/>
    <ul>
        <li><a href="index.php?mod=sync&act=download"><b><?php echo _('Export data'); ?> </b></a><br/><?php echo _('Save the information of selected modules to XML, CSV, SQL or SQLite in compressed or uncompressed file formats'); ?></li>
        <li><a href="index.php?mod=sync&act=upload"><b><?php echo _('Import data'); ?> </b> </a><br/><?php echo _('Update Sahana database with information \'exported\' from another Sahana installation.'); ?></li>
        <li><a href="index.php?mod=sync&act=history"><b><?php echo _('History'); ?></b></a><br/><?php echo _('Lists all synchronizations done in the past.'); ?></li>
        
	</ul>
<br/>   
        


<!--<center><em class="red">This module is still under heavy development It is not advisable to use it for practical purposes</em></center> -->
</div>
