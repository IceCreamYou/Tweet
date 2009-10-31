// $Id$

=============
== Summary ==
=============
This module provides links to post pages to twitter. Clicking the links will
open a new window or tab with twitter in it. The tweet will be in focus and will
contain a customizable string which can programmatically include the relevant
URL, title, and (if the tweet link appears on a node) taxonomy terms. The
Shorten URLs module is used to shorten the URLs if it is installed.

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

=====================
== Development/API ==
=====================
If you are using this module to display links to twitter arbitrarily, you will
probably be using the tweet_to_twitter() function.  This constructs the link
you need according to the following arguments.  All arguments are optional
unless otherwise noted.  If no arguments are passed the link constructed will
be for the current page according to your settings.

If you want more control, the _tweet_to_twitter() function takes the same
arguments and returns an array in the format required by hook_link()
(http://api.drupal.org/api/function/hook_link/6).

$type
  Specifies what will show up in the link: the twitter icon, the twitter icon
  and text, or just text. Pass 'icon' to show just the icon, 'icon_text' to
  show the icon and text, and 'text' to show just the text. Required if display
  options for nodes are set to 'none' on the settings page.
$format
  A string representing the tweet text, optionally with the case-insensitive
  tokens [url], [title], and [node-tags]. If not passed, the format from the
  settings page will be used.
$nid
  The NID of the node for which the twitter link should be constructed, or
  the absolute URL of the page for which the twitter link should be
  constructed. If the URL given is not the current URL, and if $nid is not a
  NID, the title must be set manually (instead of using the [title] token) or
  it will be incorrect.

==================
== Installation ==
==================
   1. Install this module as usual (FTP the files to sites/all/modules, enable 
        at admin/build/modules).  See http://drupal.org/node/176044 for help.
   2. If you want, go to admin/settings/tweet to change the module's settings.

===========
== Links ==
===========
Visit the module page for more information.

Module Page: http://drupal.org/project/tweet
Enable Module: http://example.com/?q=admin/build/modules
Settings Page: http://example.com/?q=admin/settings/tweet
Shorten URLs: http://drupal.org/project/shorten