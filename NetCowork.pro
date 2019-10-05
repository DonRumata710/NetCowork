TEMPLATE = subdirs

SUBDIRS = \
    Generator \
    NetCowork \
    Example

Example.depends = NetCowork
