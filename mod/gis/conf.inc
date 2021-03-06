<?php
/* $id$ */
/** Configuration File for GIS
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * Sahana - http://sahana.sourceforge.net
 * @author   Mifan Careem <mifan@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage gis
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
include_once ('conf_help.inc');
/**
 *provide a  nice display name for the GIS module
 */
global $conf;
$conf['mod_gis_name'] = _("Situation Mapping");
$conf['mod_gis_menuorder'] = 2;
/**
 * Nice name for admin module
 */
$conf['mod_gis_adm_name'] = _("GIS");
/**
 * Default GIS plugin to use as GIS.
 * Can be changed via the admin interface for GIS
 * Should be the directory name of the GIS plugin
 */
$conf['mod_gis_dflt'] = 'google_maps';
# if google maps, map api key
# key should be registered to hosted url
//@deprecated
//$conf['gmap_key'] = 'ABQIAAAAb-bE-ljr4-6Hsb4x92lWhRT2yXp_ZAY8_ufC3CFXhHIE1NvwkxQTjccCsxIjr0poUEEARUZJgolNfw';
//new value
$conf['mod_gis_google_key'] = 'ABQIAAAAb-bE-ljr4-6Hsb4x92lWhRT2yXp_ZAY8_ufC3CFXhHIE1NvwkxQTjccCsxIjr0poUEEARUZJgolNfw';
//$conf['mod_gis_google_key']='ABQIAAAAb-bE-';

/**
 * Default center coordinates of displayed maps
 * Currently set to display Sri Lanka as default
 * Can be changed via the admin interface for GIS
 */
$conf['mod_gis_center_x'] = '79.4'; //longitude
$conf['mod_gis_center_y'] = '6'; //latitude
$conf['mod_gis_zoom'] = '7';
/**
 * folder that contains gis data files
 */
$conf['mod_gis_data_folder'] = 'data';
/**
 * Map dimensions
 */
$conf['mod_gis_height'] = 600;
$conf['mod_gis_width'] = 760;
/**
 * folder to store custom markers
 * given from sahana root
 */
$conf['mod_gis_marker_folder'] = 'theme/default/img/';
/**
 * folder to store wiki images
 * given from sahana root
 */
$conf['mod_gis_image_folder'] = 'www/tmp/';
/**
 * folder to store temp images of maps
 * given from sahana root
 */
$conf['mod_gis_tmp_image_folder'] = 'theme/default/img/';
/**
 * Configuration specific to OpenLayers
 * @TODO: move functionality to upcoming GeoCatalogue module :)
 */
/**
 * Switch for Googlemaps
 * 0 for off; 1 for on
 */
$conf['ol_google_hybrid'] = '1';
$conf['ol_google_maps'] = '1';
$conf['ol_google_sat'] = '1';
/**
 * Switch for MS Virtual Earth
 * 0 for off; 1 for on
 */
$conf['ol_virtualearth'] = '0';
/**
 * Switch for MultiMap
 * 0 for off; 1 for on
 */
$conf['ol_multimap'] = '0';
$conf['mod_gis_multimap_key'] = 'metacarta_04';
/**
 * Switch for Yahoo! maps
 * 0 for off; 1 for on
 */
$conf['ol_yahoo_maps'] = '1';
$conf['mod_gis_yahoo_key'] = 'euzuro-openlayers';
/**
 * Counter for OpenLayers WMS layers
 * 0 for off; positive integer for how many layers are on
 */
$conf['ol_wms'] = '1';
$conf['ol_wms_1_description'] = '';
$conf['ol_wms_1_name'] = 'VMap0';
$conf['ol_wms_1_type'] = 'base';
$conf['ol_wms_1_url'] = 'http://labs.metacarta.com/wms/vmap0';
$conf['ol_wms_1_layers'] = 'basic';
$conf['ol_wms_1_img'] = '';
$conf['ol_wms_1_transparency'] = '0';
$conf['ol_wms_1_min'] = '';
$conf['ol_wms_1_max'] = '';
$conf['ol_wms_2_description'] = '';
$conf['ol_wms_2_name'] = 'VMap1';
$conf['ol_wms_2_type'] = 'base';
$conf['ol_wms_2_url'] = 'http://labs.metacarta.com/wms/vmap0';
$conf['ol_wms_2_layers'] = 'basic';
$conf['ol_wms_2_img'] = '';
$conf['ol_wms_2_transparency'] = '0';
$conf['ol_wms_2_min'] = '';
$conf['ol_wms_2_max'] = '';
/**
 * Counter for OpenLayers GeoRSS layers
 * 0 for off; positive integer for how many layers are on
 */
$conf['ol_georss'] = '0';
$conf['ol_georss_1_description'] = '';
$conf['ol_georss_1_name'] = 'Earthquakes';
$conf['ol_georss_1_url'] = 'http://earthquake.usgs.gov/eqcenter/catalogs/eqs7day-M2.5.xml';
?>
