import re
import string

# Print the list of items and quantities to console
def PrintListToConsole(item_quantities):
   # Used for formatting
   list_border = '-'
   list_width = 15

   # Print header
   print(list_border * list_width)
   print("Item(s) Sold:")
   print(list_border * list_width)

   # Print list of items and quantity
   for item, quantity in item_quantities.items():
      print("{}: {}".format(item, quantity))

   # Print footer
   print(list_border * list_width)


# Writes list data to a file
def WriteListToFile(item_quantities):
   # Open the file with write permissions
   with open('frequency.dat', 'w') as write_file:
      # Loop dictionary and write it's key and value to the file
      for i, (item, quantity) in enumerate(item_quantities.items()):
         write_file.write("{} {}".format(item, quantity))

         # I kept track of the index so that I didn't write an extra newline at the end of the file
         # This writes a newline if we are NOT at the end of the dictionary
         if (i != len(item_quantities) - 1):
            write_file.write("\n")


            # Main "driver" function of my Python code
# Looks up a grocery item(s) in a file list and displays that item's sell quantity in various ways:
# If the item string is empty, it prints all items in the list to the console
# If the item string is 'histogram', it writes a list of items to a file
# If the item string is anything else, aka a specific item 'apples', it searches for the item in the list and prints it to console if found
def PrintItemSaleFrequency(itemToLookup):
   grocery_list = []      # List of only items sold for reading input
   item_quantities = {}   # Dictionary of items with quantities

   # Open the raw data file provided
   with open("CS210_Project_Three_Input_File.dat") as file:
      # Read and split the data into a list for easy manipulation
      grocery_list = file.read().split()

   # Sort the list alphabetically (just because I want to; it looks nicer and the order doesn't matter)
   grocery_list.sort()

   # If looking up a specific item, lookup and return the quantity
   if itemToLookup and (itemToLookup != "histogram"):
      return grocery_list.count(itemToLookup.capitalize())

   # Otherwise, build a dictionary of items with quantities
   # For each item in the list...
   for item in grocery_list:
      # If the item isn't in the dictionary yet...
      if item not in item_quantities:
         # Add an entry to the dictionary starting at quantity 1
         item_quantities[item] = 1
      else:
         # Else increment the quantity of the existing item
         item_quantities[item] += 1
   
   # If a histogram style was specified, write the data to a file
   if itemToLookup == "histogram":
      WriteListToFile(item_quantities)
   # Otherwise print the list to console
   else:
      PrintListToConsole(item_quantities)
   
   return 0;
