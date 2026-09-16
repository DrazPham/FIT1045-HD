# FIT1045-HD

A real-time multiplayer house-buying app built in pure C++, combining a swipe-based browsing experience with live auctions between matched users. Work in progress — see README for details.

# MORE INFORMATION

# HouseMatch (working title)

A real-time multiplayer house-buying app built in pure C++.

The core idea combines a Tinder-style browsing experience with a live auction system. Each user gets their own screen where houses pop up one at a time, and they simply choose Yes or No. If a user picks Yes, they enter a waiting room tied to that specific house. Once another user also picks Yes for the same house, both users are matched together and a live auction begins between them for that property.

This project is built entirely in C++, with a focus on handling multiple concurrent users and keeping their sessions synchronized in real time — matching users, managing waiting rooms, and running live auction sessions without conflicts.

Currently a work in progress. Planned features include:

- Real-time user matching per house listing
- Live bidding/auction system between matched users
- Persistent house data (images, price, details) shared across users
- Clean per-user GUI for browsing and bidding

Networking approach is still being finalized — exploring options for handling concurrent connections and real-time state sync in C++.

Feedback, ideas, and contributions are welcome!
