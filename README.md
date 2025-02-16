# Factory
C++ project
Implement a program in C++ to represent a Factory that sells its production to store suppliers. The
factory has different divisions which produce different artifacts. Artifacts are sold for a certain price and can
have a discount. The factory also offers Services to its clients – e.g. custom development.

1. Division
Data Slots:
• GUID (string) – e.g. ABCD-EFGH-1234
• Name (string) – e.g. Electronics
• PhoneNumber (string) – e.g. 0888 123456
• Description (long string)
• Parent (Division) – a parent division, can be NULL
Methods:
• Constructor(s)
Axioms:
• GUID must be unique across other divisions’ GUIDs

2. Artifact
Data Slots:
• GUID (string)
• Name (string) – e.g. Sony Vaio
• Description (long string)
• Category (string) – the artifact category – e.g. Laptop
• Division (Division) – division to which the artifact belongs; cannot be empty
• Price (double) – e.g. 185.99
• Discount (double) – e.g. 30
• DiscountType (enum) – amount or percentage
• Quantity (number)
Methods:
• Constructor(s)
• double GetEffectivePrice {
• If DiscountType is amount:
• Return Price – Discount
• Else:
• Return Price – Price * Discount / 100
• }
• double GetTotalPrice { Return Quantity * GetEffectivePrice() }
Axioms:
• Price, Discount and Quantity cannot be negative
• GetEffectivePrice() and GetTotalPrice() should not return a negative amount

4. Service (inherits Artifact)
Own Data Slots:
• Duration (double) – e.g. 1.5 (service execution duration in hours)
• Rate (double) – e.g. 8.50
• RateDiscount (double) – e.g. 30
• RateDiscountType – amount or percentage
Methods:
• Constructor(s)
• double GetEffectiveRate {
• If RateDiscountType is amount:
• Return Rate – RateDiscount
• Else:
• Return Rate – Rate * RateDiscount / 100
• }
• double GetTotalPrice { Artifact::GetTotalPrice() + GetEffectiveRate() * Duration }
Axioms:
• Duration, Rate and RateDiscount cannot be negative
• GetEffectiveRate() and GetTotalPrice() should not return negative amount

Driver Program:
1. Define three vectors for storing the data for the Market Store:
(1) Divisions – pointers of object instances of class Divisions available for your store
(2) Artifacts – pointers of instances of Artifact
(3) Services – pointers of instances of Service
2. Add code to implement the following functionality in the rest of the driver program:
(1) Add at least three new divisions to the Divisions collection
(2) Add at least three artifacts to the Artifact list, which have a correct Division from the list of
available and instantiated divisions in the previous step
(3) Add at least three services to the Services list, having a valid Division
(4) Use two loops to show the Name and Total Price of each artifact and service in the store
