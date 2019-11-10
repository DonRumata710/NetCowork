TEMPLATE = subdirs

SUBDIRS = \
    Generator \
    NetCowork \
    Examples \
    Tests

Examples.depends = NetCowork Generator
Tests.depends = NetCowork
