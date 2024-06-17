//
// Created by user on 12/03/2024.
//



#include "Omsterdam.h"



Omsterdam::Omsterdam() {
    graph = make_shared<DirectedGraph>();
    rev_graph = make_shared<DirectedGraph>();

    waiting_times["bus"] = 2;
    waiting_times["tram"] = 3;
    waiting_times["sprinter"] = 4;
    waiting_times["rail"] = 5;

    transit_times["intercity"] = 15;
    transit_times["stad"] = 10;
    transit_times["centraal"] = 5;

    out_file="output.dat";
}

void Omsterdam::read_config(const string &file) {
    if(!is_file_exist(file)){
        string err = "cannot find file: " + file;
        throw FileNotFound(err);
    }
    ifstream my_file(file, ios::in);
    string type_change,change;
    int i = 1;
    while (my_file >> type_change >> change){
        if(type_change=="bus"){
            waiting_times[type_change] = stoi(change);
        }
        else if(type_change=="tram"){
            waiting_times[type_change] = stoi(change);
        }
        else if(type_change=="sprinter"){
            waiting_times[type_change] = stoi(change);
        }
        else if(type_change=="rail"){
            waiting_times[type_change] = stoi(change);
        }
        else if(type_change=="intercity"){
            transit_times[type_change] = stoi(change);
        }
        else if(type_change=="stad"){
            transit_times[type_change] = stoi(change);
        }
        else if(type_change=="centraal"){
            transit_times[type_change] = stoi(change);
        }
        else{
            cout<<"invalid configuration line: "<<i<<endl;
        }
        i++;
    }


}

void Omsterdam::read_files(const string &file) {
    if(!is_file_exist(file)){
        string err = "cannot find file: " + file;
        throw FileNotFound(err);
    }
    ifstream my_file(file, ios::in);

    size_t prefix_bus = file.rfind("bus", 0);
    size_t prefix_tram = file.rfind("tram", 0);
    size_t prefix_sprinter = file.rfind("sprinter", 0);
    size_t prefix_rail = file.rfind("rail", 0);

    string source, target, temp;
    int weight;

    if (prefix_bus == 0) {
        while (my_file >> source >> target >> temp) {
            validate(source);
            validate(target);
            validate_integer(temp, file);
            weight = stoi(temp);
            graph->putEdge(source, target, weight, "bus");
            rev_graph->putEdge(target, source, weight, "bus");
        }
    } else if (prefix_tram == 0) {
        while (my_file >> source >> target >> temp) {
            validate(source);
            validate(target);
            validate_integer(temp, file);
            weight = stoi(temp);
            graph->putEdge(source, target, weight, "tram");
            rev_graph->putEdge(target, source, weight, "tram");
        }
    } else if (prefix_sprinter == 0) {
        while (my_file >> source >> target >> temp) {
            validate(source);
            validate(target);
            validate_integer(temp, file);
            weight = stoi(temp);
            graph->putEdge(source, target, weight, "sprinter");
            rev_graph->putEdge(target, source, weight, "sprinter");
        }
    } else if (prefix_rail == 0) {
        while (my_file >> source >> target >> temp) {
            validate(source);
            validate(target);
            validate_integer(temp, file);
            weight = stoi(temp);
            graph->putEdge(source, target, weight, "rail");
            rev_graph->putEdge(target, source, weight, "rail");
        }
    }
    my_file.close();
}

bool Omsterdam::validate(const string &str) {
    if (str.length() > 16 || str == "exit")
        throw runtime_error("invalid source/target.");
    return true;
}

bool Omsterdam::validate_integer(const string &str, const string &file) {
    for (char i: str) {
        if (!isdigit(i))
            cerr << "ERROR: node definition in " << file << " is invalid\n";
    }
    return true;
}

void Omsterdam::write_file(const string &str) {
    ofstream file;
    string line;
    file.open(str);
    graph->print_graph(str);
    file.close();
}


bool Omsterdam::is_file_exist(const string &fileName) {
    ifstream infile(fileName, ios::in);
    if (infile) {
        infile.close();
        return true;
    }
    return false;
}

void Omsterdam::user_interface() {
    string user_input;

    while (true) {
        cin >> user_input;
        if (user_input == "load") {
            cin >> user_input;
            if (is_file_exist(user_input)) {
                read_files(user_input);
                cout << "Update was successful." << endl;
            } else {
                cerr << "ERROR opening the specified file." << endl;
            }
        } else if (user_input == "outbound") {
            cin >> user_input;
            if(!graph->containVertex(user_input)){
                cerr<<user_input<<" does not exist in the current network"<<endl;
                break;
            }
            cout << "bus: ";
            out_bound(*graph, user_input, "bus");
            cout << endl;
            cout << "tram: ";
            out_bound(*graph, user_input, "tram");
            cout << endl;
            cout << "sprinter: ";
            out_bound(*graph, user_input, "sprinter");
            cout << endl;
            cout << "rail: ";
            out_bound(*graph, user_input, "rail");
            cout << endl;
        } else if (user_input == "inbound") {
            cin >> user_input;
            if(!graph->containVertex(user_input)){
                cerr<<user_input<<" does not exist in the current network"<<endl;
                break;
            }
            cout << "bus: ";
            out_bound(*rev_graph, user_input, "bus");
            cout << endl;
            cout << "tram: ";
            out_bound(*rev_graph, user_input, "tram");
            cout << endl;
            cout << "sprinter: ";
            out_bound(*rev_graph, user_input, "sprinter");
            cout << endl;
            cout << "rail: ";
            out_bound(*rev_graph, user_input, "rail");
            cout << endl;
        } else if (user_input == "uniExpress") {
            string target;
            cin >> user_input;
            cin >> target;
            if(!graph->containVertex(user_input)){
                cerr<<user_input<<" does not exist in the current network"<<endl;
                break;
            }
            if(!graph->containVertex(target)){
                cerr<<target<<" does not exist in the current network"<<endl;
                break;
            }
            cout << "bus: ";
            dijkstra(*graph, user_input, "bus", target);
            cout << endl;
            cout << "tram: ";
            dijkstra(*graph, user_input, "tram", target);
            cout << endl;
            cout << "sprinter: ";
            dijkstra(*graph, user_input, "sprinter", target);
            cout << endl;
            cout << "rail: ";
            dijkstra(*graph, user_input, "rail", target);
            cout << endl;
        } else if (user_input == "multiExpress") {
            string target;
            cin >> user_input;
            cin >> target;
            if(!graph->containVertex(user_input)){
                cerr<<user_input<<" does not exist in the current network"<<endl;
                break;
            }
            if(!graph->containVertex(target)){
                cerr<<target<<" does not exist in the current network"<<endl;
                break;
            }
            double x = dijkstra_trans(*graph, user_input, target);
            cout << "multiExpress: ";
            cout << x << endl;
        } else if (user_input == "viaExpress") {
            string target;
            string transit;
            cin >> user_input;
            cin >> transit;
            cin >> target;
            if(!graph->containVertex(user_input)){
                cerr<<user_input<<" does not exist in the current network"<<endl;
                break;
            }
            if(!graph->containVertex(target)){
                cerr<<target<<" does not exist in the current network"<<endl;
                break;
            }
            double x = dijkstra_trans(*graph, user_input, transit);
            double y = dijkstra_trans(*graph, user_input, target);
            cout << "viaExpress: ";
            cout << x + y << endl;
        } else if (user_input == "print") {
            graph->print_graph(out_file);
        } else if (user_input == "exit") {
            break;
        } else {
            cerr << "Invalid command" << endl;
        }
    }
}


void Omsterdam::out_bound(DirectedGraph dg, const string &startNode, const string &type) {
    queue<string> q;
    vector<string> visited;
    bool is_empty = true;
    visited.push_back(startNode);
    q.push(startNode);

    while (!q.empty()) {
        string currentNode = q.front();
        q.pop();
        if (currentNode != startNode) {
            is_empty = false;
            cout << currentNode << "\t";
        }
        for (const string &neighbor: dg.get_neighbors_transport(currentNode, type)) {
            if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                visited.push_back(neighbor);
                q.push(neighbor);
            }
        }
    }
    if (is_empty) {
        cout << "no outbound travel";
    }
}

void Omsterdam::dijkstra(DirectedGraph dg, const string &start, const string &type, const string &target) {
    map<string, double> dist;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    map<string, vector<shared_ptr<Edge>>> graph = dg.getGraph();

    for (const auto &entry: dg.getGraph()) {
        dist[entry.first] = numeric_limits<double>::infinity();
    }

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        for (const auto &edge: dg.get_neighbors_edges(u, type)) {
            string v = (*edge).v2;
            double weight = (*edge).weight + waiting_times[type];

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);

            }
        }
    }

    if (dist[target] != numeric_limits<double>::infinity()) {
        cout << dist[target] - waiting_times[type];
    } else {
        cout << "route unavailable";
    }
}

double Omsterdam::dijkstra_trans(DirectedGraph dg, const string &start, const string &target) {
    map<string, double> dist;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    map<string, vector<shared_ptr<Edge>>> graph = dg.getGraph();

    for (const auto &entry: dg.getGraph()) {
        dist[entry.first] = numeric_limits<double>::infinity();
    }

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        for (const auto &edge: dg.get_neighbors_edges(u)) {
            string v = (*edge).v2;
            double weight = (*edge).weight;
            string stype = getStationType(v);
            if (stype == "intercity") {
                weight += transit_times[stype];
            } else if (stype == "centraal") {
                weight += transit_times[stype];
            } else {
                stype = "stad";
                weight += transit_times[stype];
            }

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    if (dist[target] != numeric_limits<double>::infinity()) {
        return dist[target] - transit_times[getStationType(target)];
    }

    cout << "route unavailable" << endl;

    return -1;
}

string Omsterdam::getStationType(const string &str) {
    string res = "stad";
    if (str.rfind("IC", 0) == 0) {
        res = "intercity";
        return res;
    } else if (str.rfind("CS", 0) == 0) {
        res = "centraal";
        return res;
    }
    return res;
}

void Omsterdam::setOutFile(const string &outFile) {
    out_file = outFile;
}



void out_bound(DirectedGraph dg, const string &startNode) {

    queue<string> q;
    vector<string> visited;
    bool is_empty = true;
    visited.push_back(startNode);
    q.push(startNode);

    while (!q.empty()) {
        string currentNode = q.front();
        q.pop();
        if (currentNode != startNode) {
            is_empty = false;
            cout << currentNode << "\t";
        }
        for (string neighbor: dg.get_neighbors(currentNode)) {
            if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                visited.push_back(neighbor);
                q.push(neighbor);
            }
        }
    }
    if (is_empty) {
        cout << "no outbound travel";
    }
}


void dfs(DirectedGraph &dg, const string &node, vector<string> &visited, bool &is_empty, const string &startNode) {
    // Mark the current node as visited
    visited.push_back(node);

    // For every predecessor of the current node
    for (const string &predecessor: dg.get_neighbors(node)) {
        // If the predecessor is not yet visited
        if (find(visited.begin(), visited.end(), predecessor) == visited.end()) {
            if (predecessor != startNode) {
                is_empty = false;
                cout << predecessor << "\t";
            }
            dfs(dg, predecessor, visited, is_empty, startNode);
        }
    }
}

void in_bound(DirectedGraph dg, const string &startNode) {
    vector<string> visited;
    bool is_empty = true;


    dfs(dg, startNode, visited, is_empty, startNode);

    if (is_empty) {
        cout << "no inbound travel";
    }
}