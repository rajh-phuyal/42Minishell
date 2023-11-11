/*
function tokenList() {
    if (nextToken() is name) {
        while (nextToken() is name) {
            continue;
        }
        return success;
    } else if (nextToken() is arg) {
        while (nextToken() is arg) {
            continue;
        }
        return success;
    } else if (nextToken() is redir) {
        if (nextToken() is redirIn) {
            if (nextToken() is file) {
                continue;
            } else {
                return error("Expected file after redirection");
            }
        } else if (nextToken() is redirOut) {
            if (nextToken() is file) {
                continue;
            } else {
                return error("Expected file after redirection");
            }
        } else {
            return error("Invalid redirection");
        }
        return success;
    } else {
        return error("Invalid token");
    }
}
*/