use std::collections::HashSet;
use std::fs::File;
use std::io::Write;
use std::path::Path;
use std::process::ExitCode;
use std::{env, fs};

fn split_commands(content: String) -> Vec<String> {
    let mut commands = Vec::new();
    let mut current_command = String::new();
    let mut last_backslash: bool = false;

    let mut iter = content.chars().peekable();

    while let Some(ch) = iter.next() {
        match ch {
            '\n' => {
                if last_backslash {
                    current_command.push(ch);
                } else {
                    commands.push(current_command.to_owned());
                    current_command.clear();
                }
                last_backslash = false;
            }
            '\\' => {
                last_backslash = true;
                current_command.push(ch);
            }
            _ => {
                last_backslash = false;
                current_command.push(ch);
            }
        }
    }

    if !current_command.is_empty() {
        commands.push(current_command);
    }

    commands
}

fn main() -> ExitCode {
    let mut args = env::args();

    let len = args.len();
    if len < 2 || len > 3 {
        eprintln!("Usage: {} <histfile_path>", args.nth(0).unwrap());
        return ExitCode::FAILURE;
    }

    let histfile = args.nth(1).unwrap();

    let histfile_path = Path::new(&histfile);
    if !histfile_path.exists() {
        eprintln!("Histfile does not exist at: {}", histfile);
        return ExitCode::FAILURE;
    }

    let histfile_content = fs::read_to_string(histfile_path).unwrap();

    let backup_hist = format!("{}.bak", histfile);
    let mut backup_file = File::create(&backup_hist).unwrap();
    backup_file
        .write_all(histfile_content.as_bytes())
        .expect("Failed to write to backup file. Cannot continue");

    let commands: HashSet<String> = split_commands(histfile_content).drain(..).collect();

    let mut histfile = File::create(histfile_path).unwrap();
    for command in commands {
        match histfile.write_all(command.as_bytes()) {
            Ok(_) => {}
            Err(e) => {
                eprintln!("Error writing command to histfile: {}", e);
            }
        }

        histfile.write(b"\n").unwrap();
    }

    println!("File {} optimized.", histfile_path.display());

    ExitCode::SUCCESS
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_split_commands() {
        let commands = [
            "echo hello",
            "echo world",
            "echo this is a test",
            "echo this is a test\\\n\techo this is a test",
            "echo this is a test\\\necho this is a test",
            "ls -a; echo hello && \\\n\techo world",
        ];

        let split_commands = split_commands(commands.join("\n"));

        assert_eq!(split_commands.len(), commands.len());

        for (i, command) in commands.iter().enumerate() {
            assert_eq!(split_commands[i], *command);
        }
    }
}
