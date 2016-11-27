/**
 Copyright 2016 Otavio Rodolfo Piske
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
#include "gru_base.h"

const char *gru_base_app_home(const char *appname) {
	char *filename = NULL;

#if defined(_WIN32) || defined(_WIN64)
	const char *home = getenv("HOMEPATH");

	asprintf(&filename, "%s/.%s", home, appname);
#else
	struct passwd *pw = getpwuid(getuid());
        

	asprintf(&filename, "%s/.%s", pw->pw_dir, appname);
        
	
#endif
	return filename;
}