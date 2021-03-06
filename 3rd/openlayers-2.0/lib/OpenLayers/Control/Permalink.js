/* Copyright (c) 2006 MetaCarta, Inc., published under the BSD license.
 * See http://svn.openlayers.org/trunk/openlayers/license.txt for the full
 * text of the license. */

/**
 * @class
 * 
 * @requires OpenLayers/Control.js
 */
OpenLayers.Control.Permalink = Class.create();
OpenLayers.Control.Permalink.prototype = 
  Object.extend( new OpenLayers.Control(), {

    /** @type DOMElement */
    element: null,
    
    /** @type String */
    base: '',
    
    /**
     * @constructor
     * 
     * @param {DOMElement} element
     * @param {String} base
     */
    initialize: function(element, base) {
        OpenLayers.Control.prototype.initialize.apply(this, arguments);
        this.element = element;        
        if (base) this.base = base;
    },

    /**
     * @type DOMElement
     */    
    draw: function() {
        OpenLayers.Control.prototype.draw.apply(this, arguments);
        var args = OpenLayers.Util.getArgs();
        if (args.lat && args.lon) {
            this.map.setCenter(
               new OpenLayers.LonLat(parseFloat(args.lon), parseFloat(args.lat))
            );
        }
        if (args.zoom) {
            this.map.zoomTo(parseInt(args.zoom));
        }
        if (!this.element) {
            this.element = document.createElement("a");
            this.div.style.right = "3px";
            this.div.style.bottom = "3px";
            this.div.style.left = "";
            this.div.style.top = "";
            this.div.style.display = "block";
            this.div.style.position = "absolute";
            this.element.style.fontSize="smaller";
            this.element.innerHTML = "Permalink";
            this.element.href="";
            this.div.appendChild(this.element);
        }
        this.map.events.register( 'moveend', this, this.updateLink);
        return this.div;
    },
   
    /**
     * 
     */
    updateLink: function() {
        var center = this.map.getCenter();
        var zoom = this.map.getZoom(); 
        var lat = Math.round(center.lat*100000)/100000;
        var lon = Math.round(center.lon*100000)/100000;
        this.element.href = this.base+"?lat="+lat+"&lon="+lon+"&zoom="+zoom; 
    }, 
    
    /** @final @type String */
    CLASS_NAME: "OpenLayers.Control.Permalink"
});

