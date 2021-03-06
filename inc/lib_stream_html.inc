<?php
/* $Id: lib_stream_html.inc,v 1.12.2.1 2008/05/20 13:05:27 ishanul Exp $ */
/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage stream_html
 * @author     Chamindra de Silva <chamindra@opensource.lk>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
function shn_stream_init() {
    global $global;
    global $conf;
    require_once ($global['approot'] . 'inc/lib_security/lib_acl.inc');
    $module = $global['module'];
    // include the html head tags
    shn_include_page_section('html_head', $module);
    // Start the body and the CSS container element
    
?>
    <?php if (isset($_SESSION['admin']['locale']['enable']) && $_SESSION['admin']['locale']['enable'] == "set") { ?>
    	<body onclick="whichElement(event)" oncontextmenu="return false;">
    <?php
    } else { ?>
    	<body>	
    <?php
    } ?>
    <div id="container">
<?php
    // include the page header provided there is not a module override
    shn_include_page_section('header', $module);
    // Now include the wrapper for the main content
    
?>     
    <div id="wrapper" class="clearfix"> 
    <div id="wrapper_menu">
    <p id="skip">Jump to: <a href="#content"><?php echo _('Content') ?></a> | <a href="#modulemenu"><?php echo _('Module Menu') ?></a></p> 
<?php
    // hack for the admin section such that the mene and login come from
    // the admin section
    if (isset($global['effective_module']) && $global['effective_module'] != null) {
        $module = $global['effective_module'];
    }
    // include the mainmenu and login provided there is not a module override
    shn_include_page_section('mainmenu', $module);
    if (shn_acl_is_enabled() == true) {
        shn_include_page_section('login', $module);
    }
    // display the breadcrumbs: It is important that this happens after the menu definition
    // the nice name is constructed from the query string
    $nicename = 'shn_q_' . $_SERVER['QUERY_STRING'] . '_nicename';
    if (array_key_exists($nicename, $global)) shn_breadcrumb_push($global[$nicename]);
    shn_breadcrumb_display();
    // now include the main content of the page
    
?>  
    </div> <!-- Left hand side menus & login form -->
    <div id="content" class="clearfix">      
<?php
    ob_start(); // start output buffer for the module output
    
}
function shn_stream_close() {
    global $global;
    // flush the output buffer
    $output = ob_get_contents();
    ob_end_clean();
    // display the errors first before the rest of the module output
    display_errors();
    display_submit_message('confirmation', _('Submission Successful'));
    display_submit_message('warning', _('Warning'));
    echo $output;
?>
    </div> <!-- /content -->
<?php
    // include the footer provided there is not a module override
    shn_include_page_section('footer', $global['module']);
?>
    </div> <!-- /wrapper -->
    </div> <!-- /container -->
    </body>
    </html>
<?php
}
?>
