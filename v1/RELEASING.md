# Releasing

1. Update version in `src/macros.h`
2. Update `CHANGELOG.md`
3. Update `SECURITY.md`
4. Check the year of copyright notices is equal to `${START_YEAR}-${YEAR}`
5. Commit changes
6. Wait for the [Travis CI job](https://travis-ci.com/delasy/let/branches) in Active Branches
7. Update the [milestones](https://github.com/delasy/let/milestones)
8. Draft a [new GitHub release](https://github.com/delasy/let/releases/new) (just create a draft, don't publish)
9. Create `dist` directory containing installers of new version
   1. Login on:
      - Linux machine and run `scripts/gen-dist.sh linux`
      - MacOS machine and run `scripts/gen-dist.sh macos`
      - Any machine and run `scripts/gen-dist.sh`
   2. Answer promted questions
   3. Merge `dist` directories content from each machine into one directory
10. Upload content of `dist` directory to `let/let-lang.org` repository, to **dist** folder
11. Update the website

   > TODO: Describe after https://github.com/delasy/let/issues/11 landed

12. Publish drafted release
