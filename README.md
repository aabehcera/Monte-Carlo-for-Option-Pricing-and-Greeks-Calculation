# Monte Carlo for Option Pricing and Greeks Calculation

This project implements a Monte Carlo simulation for pricing options on a stock using three different strategies: bear spread, bull spread, and butterfly spread. Additionally, it calculates the Greeks (delta, gamma, theta, vega, and rho) for the options.

## File Structure

- `Header.hpp`: Contains class and function declarations.
- `Monte-Carlo.cpp`: Implements the Monte Carlo simulation for option pricing.
- `Greeks.cpp`: Implements the calculation of Greeks using the Black-Scholes model.
- `Data_Import.cpp`: Implements data importation and computation of statistics.
- `main.cpp`: Main program that interacts with the user, imports data, performs simulations, and displays results.

## Data Import

The program imports data from a CSV file named AZN.csv, which contains historical stock prices of AstraZeneca PLC from Nasdaq.
