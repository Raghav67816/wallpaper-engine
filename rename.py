from os import listdir, rename

files = listdir("./snowfall")
for index, file in enumerate(files):
    rename(f"./snowfall/{file}", f"./snowfall/{index}.jpg")
