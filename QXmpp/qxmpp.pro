include(qxmpp.pri)

TEMPLATE = subdirs

SUBDIRS = src

CONFIG += ordered

# Source distribution
QXMPP_ARCHIVE = qxmpp-0.3.0
dist.commands = \
    $(DEL_FILE) -r $$QXMPP_ARCHIVE && \
    svn export . $$QXMPP_ARCHIVE && \
    $(COPY_DIR) doc/html $$QXMPP_ARCHIVE/doc && \
    tar czf $${QXMPP_ARCHIVE}.tar.gz $$QXMPP_ARCHIVE && \
    $(DEL_FILE) -r $$QXMPP_ARCHIVE


QMAKE_EXTRA_TARGETS += dist 

