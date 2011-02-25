
=============
== Summary ==
=============
This module provides links to post pages to twitter. Clicking the links will
open a new window or tab with twitter in it. The tweet will be in focus and will
contain the URL of the relevant page on your site.  It can optionally also
contain the title of the relevant page. The URL will be abbreviated using one of
these services: hex.io, idek.net, is.gd, lin.cr, ri.ms, th8.us, or TinyURL.

URLs and titles will be for either the node which is being displayed as a
teaser or for the current page. Multiple links can appear on the same page, as
on a View of teasers. By default, links appear in the Links section when viewing
full nodes or teasers.

Administrators can choose whether to show the link as an icon, an icon and
text, or just text.  Options can be chosen separately for nodes and teasers.
Administrators can also choose which node types the links should appear on, or
could choose not to have links show up on nodes at all.  If the module is
configured not to display links automatically, administrators can display their
own links wherever they like by calling tweet_to_twitter().  A more complete
explanation is below.

==================
== Requirements ==
==================
There are no requirements for using this module, but it is recommended that your
PHP installation is compiled with either the file_get_contents() function, cURL,
or both.  If you're not sure, your PHP probably supports at least
file_get_contents(), and most installations support cURL as well.  Without one
of these, you will not be able to use the URL abbreviation feature.  For more
information visit http://php.net/file_get_contents and http://php.net/curl.

=====================
== Development/API ==
=====================
If you are using this module to display links to twitter arbitrarily, you will
probably be using the tweet_to_twitter() function.  This constructs the link
you need according to the following arguments.  All arguments are optional
unless otherwise noted.  If no arguments are passed the link constructed will
be for the current page according to your settings.

$type
  Specifies what will show up in the link: the twitter icon, the twitter icon
  and text, or just text. Pass 'icon' to show just the icon, 'icon_text' to
  show the icon and text, and 'text' to show just the text. Required if display
  options for nodes are set to 'none' on the settings page.
$title
  If FALSE, no page title will be included in the twitter message; if TRUE, the
  pagetitle will be included and will be determined from the current page or
  the NID passed to the function. If $title is a string and it is not empty,
  the string will be used as the title.  In this case @title is replaced with
  the current page's title or the title as determined from the NID passed to
  the function. If 1, the default from the settings page will be used.
$nid
  The NID of the node for which the twitter link should be constructed.
$q
  The absolute URL of the page for which the twitter link should be
  constructed. If this is not the current page, the _title_ MUST be set
  manually, or it will be incorrect.

==================
== Installation ==
==================
   1. Install this module as usual (FTP the files to sites/all/modules, enable 
        at admin/build/modules).  See http://drupal.org/node/70151 for help.
   2. If you want, go to admin/settings/tweet to change some minor 
        settings. The defaults should work for most people.

===========
== Links ==
===========
Visit the module page for more information.

Module Page: http://drupal.org/project/tweet
Enable Module: http://example.com/?q=admin/build/modules
Settings Page: http://example.com/?q=admin/settings/tweet