TEMPLATE = subdirs

SUBDIRS = \
    Generator \
    NetCowork \
    Examples \
    Tests

Examples.depends = NetCowork
Tests.depends = NetCowork
