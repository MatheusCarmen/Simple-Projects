

import requests

def get_exchange_rate(api_key, from_currency, to_currency):
    url = f"https://v6.exchangerate-api.com/v6/{api_key}/latest/{from_currency}"
    response = requests.get(url)
    if response.status_code != 200:
        print("Erro ao acessar a API")
        return None

    data = response.json()

    # Verifique se a moeda de destino está disponível
    if to_currency not in data['conversion_rates']:
        print(f"A moeda {to_currency} não está disponível.")
        return None
