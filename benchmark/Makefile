SILVA_FTP=ftp://ftp.arb-silva.de/release_123/Exports/SILVA_123_SSURef_tax_silva_trunc.fasta.gz
SILVA_LOCAL=silva/$(notdir $(SILVA_FTP))
SILVA_UNPACKED=$(subst .gz,,$(SILVA_LOCAL))

all: $(SILVA_UNPACKED)

$(SILVA_LOCAL):
	wget -O $(SILVA_LOCAL) $(SILVA_FTP)

$(SILVA_UNPACKED): $(SILVA_LOCAL)
	gunzip -k $(SILVA_LOCAL)

clean:
	rm -f $(SILVA_UNPACKED)
	@echo "Make refrained from removing $(SILVA_LOCAL). Remove this manually"
