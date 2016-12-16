#!/usr/bin/env python

import cgi
form = cgi.FieldStorage()
val1 = form.getvalue('val1')

print """
<html>
<body>
La valeur entrée est ... %s
<a href="../index.html">home</a>
</home>
</html>
""" % (val1,)
