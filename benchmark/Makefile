SILVA_FTP=ftp://ftp.arb-silva.de/release_123/Exports/
SILVA_FILE=SILVA_123_SSURef_tax_silva_trunc.fasta.gz
SILVA_DIR=silva

all: download unpack

download:
	wget -P $(SILVA_DIR) $(SILVA_FTP)/$(SILVA_FILE)
	touch $@

unpack:
	gunzip $(SILVA_DIR)/$(SILVA_FILE)

clean:
	rm $(SILVA_DIR)/$(SILVA_FILE)
