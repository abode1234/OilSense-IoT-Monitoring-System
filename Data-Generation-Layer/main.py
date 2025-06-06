import json
import random
import time 


def generate_data() ->json:
    data = {
        "timestamp": time.time(),
        "pressure": round(random.uniform(30.0, 80.0), 2),
        "temperature": round(random.uniform(60.0, 120.0), 2),
        "vibration": round(random.uniform(0.01, 0.1), 3),
        "energy_consumption": round(random.uniform(100.0, 500.0), 1)
    }
    return data


if __name__ == "__main__":
   
    all_data =[]

    for i in range(10):
        data = generate_data()
        all_data.append(data)
        print("\n",data)
        time.sleep(1)
    
    with open("data.json", "w") as f:
        json.dump(all_data, f, indent=4)
    print("Done")
