TLDExtractor
-------------------------------------------------
**Description**

A simple and easy to use Qt interface to extract TLD, domain, subdomain and registrable/registered domain of a valid host

The TLDExtractor passed test provided by "publicsuffix.org" at the bottom of "[this](https://publicsuffix.org/list/#list-format)" page.

**Usage**

```cpp
	#include "tldextractor.h"
	//
	//
	// in body of your code
	TLDExtractor tldExtractor;

	tldExtractor.setDataSearchPaths(QStringList()
		<< "/path1/to/data-file-dir"
		<< "/path2/to/test-file-dir"); // note that path1 has preceding over path2

	const QString host = QLatin1String("en.saaghar.pozh.org");

	qDebug() << tldExtractor.TLD(host) << "\n"
			<< tldExtractor.domain(host) << "\n"
			<< tldExtractor.subdomain(host) << "\n"
			<< tldExtractor.registrableDomain(host);
```
And output is as follows:
```log
org
pozh
en.saaghar
pozh.org
```

If you want to minimize function calls (one call instead four calls), then change the last line of above example as follows:
```cpp
	TLDExtractor::HostParts hostParts = tldExtractor.splitParts(host);
	
	qDebug() << hostParts.tld << "\n"
			<< hostParts.domain << "\n"
			<< hostParts.subdomain << "\n"
			<< hostParts.registrableDomain;
```


**Version**

The latest version is 1.0

**Related Links**

* https://publicsuffix.org/
* data/effective_tld_names.dat: http://mxr.mozilla.org/mozilla-central/source/netwerk/dns/effective_tld_names.dat?raw=1
* data/test_psl.txt: http://mxr.mozilla.org/mozilla-central/source/netwerk/test/unit/data/test_psl.txt?raw=1


**CopyRight**

* TLDExtractor: Copyright (C) 2014  Razi Alavizadeh (GPLv3)
* data/effective_tld_names.dat: Mozilla Public License, v. 2.0, http://mozilla.org/MPL/2.0/.
* data/test_psl.txt: http://creativecommons.org/publicdomain/zero/1.0/
