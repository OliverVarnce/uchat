#include "uchat.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getHSaccept(char *wsKey, unsigned char **dest) {
	t_SHA1Context ctx;

	if (!wsKey)
		return (-1);

	char *str = malloc(sizeof(char) * (WS_KEY_LEN + WS_MS_LEN + 1));
	unsigned char hash[SHA1HashSize];

	strcpy(str, wsKey);
	strcat(str, MAGIC_STRING);

	SHA1Reset(&ctx);
	SHA1Input(&ctx, (const uint8_t *)str, WS_KEYMS_LEN);
	SHA1Result(&ctx, hash);

	*dest = base64_encode(hash, SHA1HashSize, NULL);
	*(*dest + strlen((const char *)*dest) - 1) = '\0';
	free(str);
	return 0;
}

int getHSresponse(char *hsrequest, char **hsresponse) {
	char *s;
	unsigned char *accept;
	int ret;

	for (s = strtok(hsrequest, "\r\n"); s != NULL; s = strtok(NULL, "\r\n") )
		if (strstr(s, WS_HS_REQ) != NULL)
			break;

	s = strtok(s,    " ");
	s = strtok(NULL, " ");
	
	ret = getHSaccept(s, &accept);
	if (ret < 0)
		return (ret);

	*hsresponse = malloc(sizeof(char) * WS_HS_ACCLEN);
	strcpy(*hsresponse, WS_HS_ACCEPT);
	strcat(*hsresponse, (const char *)accept);
	strcat(*hsresponse, "\r\n\r\n");

	free(accept);
	return 0;
}
