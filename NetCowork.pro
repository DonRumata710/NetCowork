TEMPLATE = subdirs

SUBDIRS = \
    Generator \
    NetCowork \
    Examples

Examples.depends = NetCowork
