POTFILE := po/scummvm.pot
POFILES := $(wildcard po/*.po)

updatepot:
	xgettext -f po/POTFILES -d scummvm --c++ -k_ -k_t -k_s -o po/scummvm.pot \
		"--copyright-holder=ScummVM Team" --package-name=ScummVM \
		--package-version=$(VERSION) --msgid-bugs-address=scummvm-devel@lists.sf.net -o $(POTFILE)_

	sed -e 's/SOME DESCRIPTIVE TITLE/LANGUAGE translation for ScummVM/' \
		-e 's/UTF-8/CHARSET/' -e 's/PACKAGE/ScummVM/' $(POTFILE)_ > $(POTFILE).new

	rm $(POTFILE)_
	if test -f $(POTFILE); then \
		sed -f po/remove-potcdate.sed < $(POTFILE) > $(POTFILE).1 && \
		sed -f po/remove-potcdate.sed < $(POTFILE).new > $(POTFILE).2 && \
		if cmp $(POTFILE).1 $(POTFILE).2 >/dev/null 2>&1; then \
			rm -f $(POTFILE).new; \
		else \
			rm -f $(POTFILE) && \
			mv -f $(POTFILE).new $(POTFILE); \
		fi; \
		rm -f $(POTFILE).1 $(POTFILE).2; \
	else \
		mv -f $(POTFILE).new $(POTFILE); \
	fi;

po/%.po: $(POTFILE)
	msgmerge $@ $(POTFILE) -o $@.new
	if cmp $@ $@.new >/dev/null 2>&1; then \
		rm -f $@.new; \
	else \
		mv -f $@.new $@; \
	fi;

update-translations: updatepot $(POFILES)
	@$(foreach file, $(POFILES), echo -n $(notdir $(basename $(file)))": ";msgfmt --statistic $(file);)
	@rm -f messages.mo

.PHONY: updatepot update-translations