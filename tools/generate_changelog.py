import subprocess
from typing import List


def get_commits() -> List[str]:
    """
    Get the commits between the main and develop branches.
    :return: A list of commits.
    """

    # git log main..develop --pretty="%B" --reverse
    try:
        output = subprocess.check_output(
            ["git", "log", "main..develop", "--pretty=%B#", "--reverse"],
            universal_newlines=True,
        )
    except subprocess.CalledProcessError as e:
        print(f"ERROR: {e}")
        return []
    except FileNotFoundError:
        print(f"ERROR: Git not found on the system.")
        return []

    # Do some processing, ie. split the output into a list of commits
    lines = output.split("\n#")
    commits = [line.strip() for line in lines if line.strip()]

    return commits


def process_changelog() -> None:
    """
    Generate a changelog from the commits between the main and develop branches.
    """

    print("INFO: Generating changelog")
    commits = get_commits()

    for commit in commits:
        lines = commit.split("\n")
        print(f"- **{lines[0]}**")
        lines.pop(0)

        for line in lines:
            print(f"  {line}")


if __name__ == "__main__":
    process_changelog()
