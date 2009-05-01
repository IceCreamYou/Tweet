// $Id$

=============
== Summary ==
=============
This module provides links to post pages to twitter. Clicking the links will
open a new window or tab with twitter in it. The tweet will be in focus and will
contain a customizable string (making hashtags possible) which can
programmatically include the relevantURL and title. The URL will be abbreviated
using one of these services: hex.io, idek.net, is.gd, lin.cr, ri.ms, th8.us,
TinyURL, or tr.im.

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

If you want more control, the _tweet_to_twitter() function takes the same
arguments and returns an array in the format required by hook_link()
(http://api.drupal.org/api/function/hook_link/5).

$type
  Specifies what will show up in the link: the twitter icon, the twitter icon
  and text, or just text. Pass 'icon' to show just the icon, 'icon_text' to
  show the icon and text, and 'text' to show just the text. Required if display
  options for nodes are set to 'none' on the settings page.
$format
  A string representing the tweet text, optionally with the case-insensitive
  tokens [url] and [title]. If not passed, the format from the settings page
  will be used.
$nid
  The NID of the node for which the twitter link should be constructed.
$q
  The absolute URL of the page for which the twitter link should be
  constructed. If this is not the current page, the _title_ MUST be set
  manually, or it will be incorrect.

----

You can add additional URL abbreviation services to Tweet using
hook_tweet_service($original). Using this hook will expose your service to the
Tweet Settings page. If you choose the service provided by your hook there,
Tweet will process URL abbreviation as described below. See
tweet_tweet_service() for an example.

The hook should return an array keyed by the name of the service. The value of
each array element can be the URL of the service's API page that returns only
the abbreviated URL, without the site's URL appended:
'http://tinyurl.com/api-create.php?url='. If this is the case, Tweet will
automatically retrieve the abbreviated URL from the service.

The value of each array element can also be an array structured like this:
array('custom' => TRUE, 'url' => 'http://tinyurl.com/api-create.php?url='). If
'custom' is FALSE, Tweet will treat 'url' as if it was passed like a string (as
explained above). If 'custom' is TRUE, Tweet will assume the 'url' has already
been processed and will not attempt to abbreviate anything. This behavior allows
you to do your own processing--for example, you could retrieve abbreviated URLs
using JSON or XML in this manner. The 'url' returned in this case should already
be abbreviated (the parameter $original is the URL that should be abbreviated).

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