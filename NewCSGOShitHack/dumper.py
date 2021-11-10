from datetime import datetime
import requests
import json

tab = "    "
mode = "update" # update/reset

headers = {
    'User-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko)'
                  'Chrome/85.0.4183.121 Safari/537.36',
    'Accept-Language': 'en',
    'accept': '*/*',
    'origin': 'https://best.aliexpress.ru',
    'sec-fetch-site': 'cross-site',
    'sec-fetch-mode': 'cors',
    'sec-fetch-dest': 'empty',
    'referer': 'https://best.aliexpress.ru/',
    'accept-language': 'ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7'
}


def write_file(filename: str, text: str):
    with open(filename, 'w') as f:
        f.truncate()

        f.write(text)

        f.close()


def main():
    now = datetime.now()
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")

    global result_file
    result_file = f"#pragma once\n#include <iostream>\n\nnamespace offsets\n{'{'}\n    // {dt_string}\n"

    res = requests.get("https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json", headers=headers)

    if res.status_code == 200:
        print("offsets loaded successfully")

        res = res.json()
    else:
        print(f"failed to load offsets, error code: {res.status_code}")

    for val in res["signatures"]:
        if mode == "update":
            result_file += tab + "constexpr ::std::ptrdiff_t " + val + " = " + str(hex(res["signatures"][val])) + ";\n"
        elif mode == "reset":
            result_file += tab + "constexpr ::std::ptrdiff_t " + val + ";\n"

    for val in res["netvars"]:
        if mode == "update":
            result_file += tab + "constexpr ::std::ptrdiff_t " + val + " = " + str(hex(res["netvars"][val])) + ";\n"
        elif mode == "reset":
            result_file += tab + "constexpr ::std::ptrdiff_t " + val + ";\n"

    result_file += "}"

    print(result_file)

    write_file("./offsets.h", result_file)
    
    
if __name__ == '__main__':
    main()
