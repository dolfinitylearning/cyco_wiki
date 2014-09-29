(function ($) {
  Drupal.behaviors.cycoToc = {
    alreadyRun: false,
    attach: function (context, settings) {
      if ( this.alreadyRun ) {
        return;
      }
      this.alreadyRun = true;
      var headingTagList 
          = $('.swim h1, .swim h2, .swim h3, .swim h4');
      if ( headingTagList.size() > 0 ) {
        var html = '<div id="cyco_toc">'
                    + '<p id="cyco_toc_label">Contents</p>';
        var elementCount = 0;
        headingTagList.each(function(index) {
          var elementHeading = $(this).text();
          var elementTag = this.tagName.toLowerCase();
          $(this).attr('id', 'cyco_toc' + elementCount);
          html += '<p class="cyco_toc_' + elementTag + '"><a href="#cyco_toc' 
                  + elementCount + '">' + elementHeading + '</a></p>';
          elementCount ++;
        }); // end each
        html += '</div>';
        $('div.swim.textile').prepend(html);
      } // end if
    }
  };
}(jQuery));



