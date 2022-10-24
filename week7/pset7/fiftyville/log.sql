-- Keep a log of any SQL queries you execute as you solve the mystery.

--check the crime_scene_reports
.schema crime_scene_reports

SELECT description
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";


--check the interviews
SELECT name, transcript
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";


/*according to the witness's words check the
bakery_security_logs & atm_transactions & phone_calls & flights*/

--step1:check the security logs and then use the infomation to find the suspect stoler
SELECT name
FROM people
WHERE license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE
        year = 2021 AND month = 7 AND day = 28
        AND hour = 10 AND minute BETWEEN 15 AND 26);

--step2:check the atm transactions log and then use the infomation to find the suspect stoler
SELECT name
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE
            year = 2021 AND month = 7 AND day = 28
            AND atm_location = "Leggett Street" AND transaction_type = "withdraw"));

--step3:check the atm phone call log and then use the infomation to find the suspect stoler
SELECT name
FROM people
WHERE phone_number IN
    (SELECT caller
    FROM phone_calls
    WHERE
        year = 2021 AND month = 7 AND day = 28
        AND duration < 60);


--step4:check the flights log and then use the infomation to find the suspect stoler
SELECT *
FROM flights
WHERE
    year = 2021 AND month = 7 AND day = 29
ORDER BY hour;--here we find the id of the flight which stoler might take is 36


SELECT name
FROM people
WHERE passport_number IN
    (SELECT passport_number
    FROM passengers
    WHERE flight_id = 36);


/*we intersect all the outcomes then find Bruce might be the stoler*/


--as for the destination of Bruce, it's easy to get
SELECT id,city
FROM airports;-- is New York City


--finally, we get his accomplice
SELECT name
FROM people
WHERE phone_number IN
    (SELECT receiver
    FROM phone_calls
    WHERE
        year = 2021 AND month = 7 AND day = 28
        AND duration < 60
        AND caller IN
            (SELECT phone_number
            FROM people
            WHERE name = "Bruce"));--the accompice is Robin