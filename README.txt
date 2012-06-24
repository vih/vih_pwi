About Picasa Webalbum Integrator
--

This module exposes a block which makes it possible to show a block with Picasa Webalbums. It is based on the <a href="http://code.google.com/p/pwi/">Picasa Webalbum Integrator</a> javascript plugin for Jquery.

Enable the block and configure it with your username, and you have Picasa Webalbum integration.

Make sure that you <a href="http://code.google.com/p/pwi/downloads/list">download the javascript plugin</a> and install it into your libraries folder with all the contents being in the jquery.pwi-folder. 

Drush Integration
--

Instead of downloading PWI manually, drush could be used to download the plugin in sites/all/libraries if libraries module is enabled.

Drush command: 

    drush dl-pwi

In the source is also included an example on howto download PWI using drush make.

Dependencies
--

- <a href="http://drupal.org/project/libraries">libraries</a>
- <a href="http://drupal.org/project/colorbox">colorbox</a>

The module is sponsored by <a href="http://vih.dk">Vejle Idrætshøjskole</a>.
