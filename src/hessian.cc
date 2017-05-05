/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

#include "env.h"

void hessian_encode(const v8::FunctionCallbackInfo<v8::Value>& args) {
	node::Environment* env = node::Environment::GetCurrent(args);
	v8::Local<v8::Object> vbuf;
	char *data;
	size_t length;
	short ret;

	if (args[0]->IsNullOrUndefined()) {
		ret = hessian_encode_null((uint8_t**)(&data), &length);
	} else if (args[0]->IsNumber()) {
		int64_t x = args[0]->IntegerValue();
		if (x >= LONG_MAX || x < LONG_MIN) {
			ret = hessian_encode_long(x, (uint8_t**)(&data), &length);
		} else {
			ret = hessian_encode_int((int32_t)x, (uint8_t**)(&data), &length);
		}
	} else if (args[0]->IsDate()) {
		double x = args[0].As<v8::Date>()->ValueOf();
		ret = hessian_encode_date((uint64_t)x, (uint8_t**)(&data), &length);
	} else if (args[0]->IsString()) {
		v8::Local<v8::String> string = args[0].As<v8::String>();
		ret = hessian_encode_string(string, (uint8_t**)(&data), &length);
	} else {
		// TODO throw error
		return;
	}
	if (!ret) {
		// TODO throw error
		return;
	}
	vbuf = node::Buffer::New(env, data, length).ToLocalChecked();
	return args.GetReturnValue().Set(vbuf);
}

void hessian_decode(const v8::FunctionCallbackInfo<v8::Value>& args) {
	SPREAD_BUFFER_ARG(args[0], buf);
	short success;
	switch (*((uint8_t*)buf_data)) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 48:
		case 49:
		case 50:
		case 51:
		case 82:
		case 83:
			success = hessian_decode_string((uint8_t *)buf_data, buf_length, args);
			break;
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 52:
		case 53:
		case 54:
		case 55:
		case 65:
		case 66:
			success = hessian_decode_bytes((uint8_t *)buf_data, buf_length, args);
			break;
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63:
		case 76:
		case 89:
		case 216:
		case 217:
		case 218:
		case 219:
		case 220:
		case 221:
		case 222:
		case 223:
		case 224:
		case 225:
		case 226:
		case 227:
		case 228:
		case 229:
		case 230:
		case 231:
		case 232:
		case 233:
		case 234:
		case 235:
		case 236:
		case 237:
		case 238:
		case 239:
		case 240:
		case 241:
		case 242:
		case 243:
		case 244:
		case 245:
		case 246:
		case 247:
		case 248:
		case 249:
		case 250:
		case 251:
		case 252:
		case 253:
		case 254:
		case 255:
			success = hessian_decode_long((uint8_t *)buf_data, buf_length, args);
			break;
		case 67:
		case 79:
		case 91:
		case 92:
		case 93:
		case 94:
		case 95:
		case 96:
		case 97:
		case 98:
		case 99:
		case 100:
		case 101:
		case 102:
		case 103:
		case 104:
		case 105:
		case 106:
		case 107:
		case 108:
		case 109:
		case 110:
		case 111:
			success = hessian_decode_object((uint8_t *)buf_data, buf_length, args);
			break;
		case 68:
			success = hessian_decode_double((uint8_t *)buf_data, buf_length, args);
			break;
		case 70:
		case 84:
			success = hessian_decode_bool((uint8_t *)buf_data, buf_length, args);
			break;
		case 72:
			success = hessian_decode_hash_map((uint8_t *)buf_data, buf_length, args);
			break;
		case 73:
		case 128:
		case 129:
		case 130:
		case 131:
		case 132:
		case 133:
		case 134:
		case 135:
		case 136:
		case 137:
		case 138:
		case 139:
		case 140:
		case 141:
		case 142:
		case 143:
		case 144:
		case 145:
		case 146:
		case 147:
		case 148:
		case 149:
		case 150:
		case 151:
		case 152:
		case 153:
		case 154:
		case 155:
		case 156:
		case 157:
		case 158:
		case 159:
		case 160:
		case 161:
		case 162:
		case 163:
		case 164:
		case 165:
		case 166:
		case 167:
		case 168:
		case 169:
		case 170:
		case 171:
		case 172:
		case 173:
		case 174:
		case 175:
		case 176:
		case 177:
		case 178:
		case 179:
		case 180:
		case 181:
		case 182:
		case 183:
		case 184:
		case 185:
		case 186:
		case 187:
		case 188:
		case 189:
		case 190:
		case 191:
		case 192:
		case 193:
		case 194:
		case 195:
		case 196:
		case 197:
		case 198:
		case 199:
		case 200:
		case 201:
		case 202:
		case 203:
		case 204:
		case 205:
		case 206:
		case 207:
		case 208:
		case 209:
		case 210:
		case 211:
		case 212:
		case 213:
		case 214:
		case 215:
			success = hessian_decode_int((uint8_t *)buf_data, buf_length, args);
			break;
		case 74:
		case 75:
			success = hessian_decode_date((uint8_t *)buf_data, buf_length, args);
			break;
		case 77:
			success = hessian_decode_map((uint8_t *)buf_data, buf_length, args);
			break;
		case 78:
			success = hessian_decode_null((uint8_t *)buf_data, buf_length, args);
			break;
		case 81:
			success = hessian_decode_ref((uint8_t *)buf_data, buf_length, args);
			break;
		case 86:
		case 88:
		case 112:
		case 113:
		case 114:
		case 115:
		case 116:
		case 117:
		case 118:
		case 119:
		case 120:
		case 121:
		case 122:
		case 123:
		case 124:
		case 125:
		case 126:
		case 127:
			success = hessian_decode_array((uint8_t *)buf_data, buf_length, args);
			break;
		default:
			// TODO raise error
			success = 0;
	}
	if (!success) {
		// TODO throw error
	}
}
