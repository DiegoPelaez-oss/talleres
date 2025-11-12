#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Tipos y estructuras
enum class RoomType { SIMPLE, DOBLE, SUITE };

struct Room {
	int id;
	RoomType type;
	double pricePerNight;
	bool active = true;
};

struct Client {
	int id;
	string name;
	string email;
	string phone;
};

struct Reservation {
	int id;
	int clientId;
	int roomId;
	int checkIn;   // días (int)
	int checkOut;  // días (int), exclusivo
};

// Funciones auxiliares: convertir fecha "YYYY-MM-DD" a número de días (simple, sin <ctime>)
static int ymdToDays(int y, int m, int d) {
	// Algoritmo estándar para contar días (basado en calendario gregoriano)
	if (m <= 2) { y--; m += 12; }
	long long days = 365LL * y + y/4 - y/100 + y/400 + (153*(m - 3) + 2)/5 + d - 1;
	return static_cast<int>(days);
}

static int parseDate(const string& ymd) {
	// Formato esperado: "YYYY-MM-DD"
	if (ymd.size() < 10) return 0;
	int y = stoi(ymd.substr(0,4));
	int m = stoi(ymd.substr(5,2));
	int d = stoi(ymd.substr(8,2));
	return ymdToDays(y,m,d);
}

static bool rangesOverlap(int a1, int a2, int b1, int b2) {
	// Consideramos [checkIn, checkOut) semiclosed: no solapan si a2 <= b1 || b2 <= a1
	return !(a2 <= b1 || b2 <= a1);
}

// Clase (menos formal)
class Recepcion {
	vector<Room> rooms;
	vector<Client> clients;
	vector<Reservation> reservations;
	int nextRoomId = 1;
	int nextClientId = 1;
	int nextReservationId = 1;

public:
	// Registrar habitación (nombre más simple)
	int agregarHabitacion(RoomType type, double pricePerNight) {
		rooms.push_back({ nextRoomId++, type, pricePerNight, true });
		return rooms.back().id;
	}

	// Registrar cliente
	int agregarCliente(const string& name, const string& email, const string& phone) {
		clients.push_back({ nextClientId++, name, email, phone });
		return clients.back().id;
	}

	// Listar habitaciones disponibles (menos formal)
	vector<Room> habitacionesDisponibles(RoomType tipo = RoomType::SIMPLE,
	                                    const string& checkInStr = "",
	                                    const string& checkOutStr = "") const
	{
		int ci = 0, co = 0;
		bool checkDates = !checkInStr.empty() && !checkOutStr.empty();
		if (checkDates) {
			ci = parseDate(checkInStr);
			co = parseDate(checkOutStr);
		}

		vector<Room> result;
		for (const auto& r : rooms) {
			if (!r.active) continue;
			if (r.type != tipo) continue;

			bool libre = true;
			if (checkDates) {
				for (const auto& res : reservations) {
					if (res.roomId != r.id) continue;
					if (rangesOverlap(res.checkIn, res.checkOut, ci, co)) {
						libre = false;
						break;
					}
				}
			}
			if (libre) result.push_back(r);
		}
		return result;
	}

	// Hacer reserva; devuelve id o -1 si no hay
	int reservar(int clientId, RoomType desiredType,
	                                   const string& checkInStr, const string& checkOutStr)
	{
		int ci = parseDate(checkInStr);
		int co = parseDate(checkOutStr);
		if (co <= ci) return -1;

		for (const auto& r : rooms) {
			if (!r.active) continue;
			if (r.type != desiredType) continue;

			bool ocupado = false;
			for (const auto& res : reservations) {
				if (res.roomId != r.id) continue;
				if (rangesOverlap(res.checkIn, res.checkOut, ci, co)) {
					ocupado = true;
					break;
				}
			}
			if (!ocupado) {
				int resId = nextReservationId++;
				reservations.push_back({ resId, clientId, r.id, ci, co });
				return resId;
			}
		}
		return -1; // no hay habitación disponible
	}

	// Cancelar reserva por id
	bool cancelarReserva(int reservationId) {
		auto it = find_if(reservations.begin(), reservations.end(),
		                       [&](const Reservation& r) { return r.id == reservationId; });
		if (it == reservations.end()) return false;
		reservations.erase(it);
		return true;
	}

	// Calcular coste total de una reserva; devuelve -1 si no existe
	double costoReserva(int reservationId) const {
		auto it = find_if(reservations.begin(), reservations.end(),
		                       [&](const Reservation& r) { return r.id == reservationId; });
		if (it == reservations.end()) return -1.0;
		const Reservation& res = *it;

		auto roomIt = find_if(rooms.begin(), rooms.end(),
		                           [&](const Room& rm) { return rm.id == res.roomId; });
		if (roomIt == rooms.end()) return -1.0;

		double nights = static_cast<double>(res.checkOut - res.checkIn);
		if (nights < 0) nights = 0;
		return nights * roomIt->pricePerNight;
	}
};

// Main más informal
int main() {
	Recepcion r;

	// Poner algunas habitaciones
	r.agregarHabitacion(RoomType::SIMPLE, 50000.0);
	r.agregarHabitacion(RoomType::DOBLE, 80000.0);
	r.agregarHabitacion(RoomType::SUITE, 200000.0);
	r.agregarHabitacion(RoomType::DOBLE, 90000.0);

	// Un cliente
	int clientId = r.agregarCliente("Ana Perez", "anapeto@gmail.com", "+573206952458");

	// Intento de reserva
	int resId = r.reservar(clientId, RoomType::DOBLE, "2025-12-20", "2025-12-25");
	if (resId != -1) {
		cout << "Reserva exitosa!! ID: " << resId << '\n';
		double cost = r.costoReserva(resId);
		if (cost >= 0) cout << "Precio total: " << cost << " pesos\n";
	} else {
		cout << "Uy, no hay cuartos libres en esas fechas.\n";
	}

	// Mostrar cuartos dobles libres
	auto avail = r.habitacionesDisponibles(RoomType::DOBLE, "2025-12-20", "2025-12-25");
	cout << "Dobles libres: " << avail.size() << '\n';

	return 0;
}