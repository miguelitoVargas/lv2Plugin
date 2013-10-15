BUNDLE = eg-plugin.lv2
INSTALL_DIR = /usr/local/lib/lv2


$(BUNDLE): manifest.ttl myPlugin.so 

		rm -rf $(BUNDLE)
		mkdir $(BUNDLE)
		cp manifest.ttl myPlugin.so myPlugin.ttl $(BUNDLE)

myPlugin.so: myPlugin.c

		gcc -shared -fPIC -DPIC myPlugin.c `pkg-config --cflags --libs lv2-plugin` -o myPlugin.so
	
install: $(BUNDLE)

		mkdir -p $(INSTALL_DIR)
		rm -rf $(INSTALL_DIR)/$(BUNDLE)
		cp -R $(BUNDLE) $(INSTALL_DIR)
	
clean:

		rm -rf $(BUNDLE) myPlugin.so
	
